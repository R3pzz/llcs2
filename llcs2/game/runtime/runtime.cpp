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
		typedef std::uintptr_t( __cdecl *GetterFn )( );

		GetterFn		_getter{};
		const char	*_name{};
		Node				*_next{};
	};

	auto entry = *Mem{ base }.jump(
		0x3ll
	).offset(
		0x7ll
	).as< Node ** >( );

	for ( auto i = entry; i; i = i->_next ) {
		std::printf( "[InterfaceWalk] | Interface: %s (getter: %p, addr: %p, next: %p)\n",
			i->_name, i->_getter, i->_getter( ), i->_next
		);

		out.insert_or_assign( hash( i->_name ),
			i->_getter( )
		);
	}
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
	).jump( 0x3ll ).offset( 0x7ll ).as< valve::EntitySystem * >( );

	valve::gInputSystem = _knownInterfaces.at( _( "InputSystemVersion001" ) ).as< valve::InputSystem * >( );

	valve::gSchemaSystem = _knownInterfaces.at( _( "SchemaSystem_001" ) ).as< valve::SchemaSystem * >( );
}

void Runtime::extractSchemaData( ) {
	const auto scope = valve::gSchemaSystem->typeScopeForModule( "engine2.dll" );
	if ( !scope )
		return;

	const auto bindings = &scope->_bindings;

	std::printf( "[Schema] | Bindings table: %p, block size: %i, size: %i, unallocated data: %p\n",
		bindings, bindings->_blockSize, bindings->_size, bindings->_bucket._unallocatedData
	);
	
#if 0
	classes.forEachElement(
		[ &scope ]( valve::SchemaTypeScope::ClassBinding *binding ) {
			if ( !binding )
				return false;

			std::printf( "[Schema] | Found a class (bn: %s, cn: %s, mn: %s)\n",
				binding->_binName, binding->_className, binding->_moduleName
			);

			auto info = scope->findClass( binding->_binName );
			if ( !info )
			return false;

			for ( std::uint16_t i{}; i < info->_fieldSize; i++ ) {
				auto &field = info->_fields[ i ];
			}

			return false;
		}
	);
#endif
}

void Runtime::findAuxAddresses( ) {
	const auto client = _knownModules.at( _( "client.dll" ) );
	if ( !client._base._base )
		return;
}

void Runtime::initializeInput( ) {
	gInput->initializeAll( );

	std::printf( "[Main Thread] | Input initialized\n" );
}

void performTests( ) {
	std::printf( "[Schema] | Schema system found at %p\n",
		valve::gSchemaSystem
	);

	std::printf( "[Schema] | Engine.dll schema typescope at %p\n",
		valve::gSchemaSystem->typeScopeForModule( "engine2.dll" )
	);
}

void Runtime::initializeWorkers( ) {
	attachConsole( );

	extractModuleData( );

	findAuxAddresses( );

	extractSchemaData( );

	//performTests( );

	initializeInput( );

	for ( ; true; )
		std::this_thread::sleep_for( std::chrono::seconds{ 1u } );

	std::printf( "[Main Thread] | Exiting\n" );

	detachConsole( );
}