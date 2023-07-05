#include "runtime.hpp"

void parseInterfaces( const PeDesc pe,
	std::unordered_map< std::size_t, Mem > &out
) {
	const auto base = GetProcAddress(
		pe._base.as< HMODULE >( ),
		"CreateInterface"
	);

	if ( !base )
		return;

	struct Node {
		typedef
			std::uintptr_t(
				__cdecl *GetterFn
			)( );

		GetterFn		_getter{};
		const char	*_name{};
		Node				*_next{};
	};

	auto entry = *Mem{ base }.jump( 0x3 ).offset( 0x7 ).as< Node ** >( );

	for ( auto i = entry; i; i = i->_next ) {
		_LLCS2_LOG( "[InterfaceWalk] | Interface: %s (getter: %p, addr: %p, next: %p)\n",
			i->_name, i->_getter, i->_getter( ), i->_next
		);

		out.insert_or_assign( hash( i->_name ),
			i->_getter( )
		);
	}
}

void extractSchemaData( const std::string_view module,
	std::unordered_map< std::size_t, Mem > &out
) {
	const auto scope = valve::gSchemaSystem->typeScopeForModule( module.data( ) );
	if ( !scope )
		return;

	const auto bindings = &scope->_bindings;

	_LLCS2_LOG( "[SchemaWalk] | Binding table for a module %s: %p, size: %i\n",
		module.data( ), bindings, bindings->_size
	);

	bindings->forEachElement(
		[ scope, &out ]( valve::SchemaTypeScope::ClassBinding *binding ) {
			if ( !binding )
				return true;

			_LLCS2_LOG( "  [SchemaWalk] | Found a class (name: %s, at: %p)\n",
				binding->_name, binding
			);

			for ( std::uint16_t i{}; i < binding->_fieldSize; i++ ) {
				auto &field = binding->_fields[ i ];

				_LLCS2_LOG( "    [SchemaWalk] | Found a field (name: %s, type: %s, offset: %u, at: %p)\n",
					field._name, field._typeInfo->_name, field._offset, &field
				);

				char str[ 512u ]{};

				std::strcpy( str, binding->_name );
				std::strcat( str, "." );
				std::strcat( str, field._name );
				std::strcat( str, "\0" );

				out.insert_or_assign( hash( str ), field._offset );
			}

			return false;
		}
	);
}

void Runtime::attachConsole( ) {
	AllocConsole( );
	AttachConsole( ATTACH_PARENT_PROCESS );

	freopen_s( &_consoleOut, "CONOUT$", "w", stdout );
}

void Runtime::detachConsole( ) {
	std::fclose( _consoleOut );

	FreeConsole( );
}

void Runtime::extractModuleData( ) {
	const auto ldr = os::peb( )->_ldrData;

	ldr->forEachInLoadEntry(
		[ this ]( os::LdrEntry *entry ) {
			_knownModules.insert_or_assign( hash( entry->_baseDllName.wstr( ).c_str( ) ),
				PeDesc{ entry->_dllBase }
			);

			parseInterfaces( entry->_dllBase,
				_knownInterfaces
			);

			return false;
		}
	);

	const auto client = _knownModules.at( _( "client.dll" ) );
	const auto engine = _knownModules.at( _( "engine2.dll" ) );

	valve::gEntitySystem = _LLCS2_BYTESEQ( "48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 65",
		client.start( ), client.end( )
	).jump( 0x3 ).offset( 0x7 ).as< valve::EntitySystem * >( );

	valve::gInputSystem = _knownInterfaces.at( _( "InputSystemVersion001" ) ).as< valve::InputSystem * >( );

	valve::gSchemaSystem = _knownInterfaces.at( _( "SchemaSystem_001" ) ).as< valve::SchemaSystem * >( );

	ldr->forEachInLoadEntry(
		[ this ]( os::LdrEntry *entry ) {
			extractSchemaData( toNarrow( entry->_baseDllName.wstr( ) ),
				_knownOffsets
			);

			return false;
		}
	);
}

void Runtime::findAuxAddresses( ) {
	const auto client = _knownModules.at( _( "client.dll" ) );
	if ( !client._base._base )
		return;
}

void Runtime::initializeInput( ) {
	gInput->initializeAll( );

	_LLCS2_LOG( "[Main Thread] | Input initialized\n" );
}

void performTests( ) {
	
}

void Runtime::initializeWorkers( ) {
	attachConsole( );

	extractModuleData( );

	findAuxAddresses( );

	performTests( );

	initializeInput( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Initialization finished\n" );

	for ( ; true; )
		std::this_thread::sleep_for( std::chrono::seconds{ 1u } );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Exiting\n" );

	detachConsole( );
}