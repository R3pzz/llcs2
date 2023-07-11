#include <game/game.hpp>

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

	auto entry = *Mem{ base }.jump( 0x3 ).as< Node ** >( );

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
	std::unordered_map< std::size_t, std::ptrdiff_t > &out
) {
	const auto scope = valve::gSchemaSystem->typeScopeForModule( module.data( ) );
	if ( !scope )
		return;

	const auto bindings = &scope->_bindings;

	_LLCS2_LOG_IMPORTANT_F( "[SchemaWalk] | Binding table for a module %s: %p, size: %i\n",
		module.data( ), bindings, bindings->_size
	);

	bindings->forEachElement(
		[ scope, &out ]( valve::SchemaTypeScope::ClassBinding *binding ) {
			if ( !binding )
				return true;

			_LLCS2_LOG_IMPORTANT_F( "  [SchemaWalk] | Found a class (name: %s, at: %p)\n",
				binding->_name, binding
			);

			for ( std::uint16_t i{}; i < binding->_fieldSize; i++ ) {
				auto &field = binding->_fields[ i ];

				char str[ 512u ]{};

				std::strcpy( str, binding->_name );
				std::strcat( str, "." );
				std::strcat( str, field._name );
				std::strcat( str, "\0" );

				_LLCS2_LOG_IMPORTANT_F( "    [SchemaWalk] | Found a field (name: %s, type: %s, offset: %u, at: %p, hash: %zu)\n",
					str, field._typeInfo->_name, field._offset, &field, hash( str )
				);

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
	fopen_s( &_logOut, "llcs2_log.txt", "w" );
}

void Runtime::detachConsole( ) {
	std::fclose( _consoleOut );
	std::fclose( _logOut );

	FreeConsole( );
}

void Runtime::extractModuleData( ) {
	const auto ldr = os::peb( )->_ldrData;

	ldr->forEachInLoadEntry(
		[ this ]( os::LdrEntry *entry ) {
			_knownModules.insert_or_assign( hash( entry->_baseDllName.wstr( ).c_str( ) ),
				PeDesc{ entry->_dllBase }
			);

			_LLCS2_LOG( "[Main Thread] | Parsing %s..\n",
				toNarrow( entry->_baseDllName.wstr( ) ).c_str( )
			);

			parseInterfaces( entry->_dllBase,
				_knownInterfaces
			);

			return false;
		}
	);

	const auto client = _knownModules.at( _( "client.dll" ) );
	const auto engine = _knownModules.at( _( "engine2.dll" ) );
	const auto rendersystemdx11 = _knownModules.at( _( "rendersystemdx11.dll" ) );

	valve::gResourceSystem = _knownInterfaces.at( _( "GameResourceServiceClientV001" ) ).as< valve::ResourceSystem * >( );

	valve::gEntitySystem = *Mem{ valve::gResourceSystem }.offset( 0x58 ).as< valve::EntitySystem ** >( );

	valve::gInputSystem = _knownInterfaces.at( _( "InputSystemVersion001" ) ).as< valve::InputSystem * >( );

	valve::gSchemaSystem = _knownInterfaces.at( _( "SchemaSystem_001" ) ).as< valve::SchemaSystem * >( );

	valve::gRenderDeviceDx11 = _LLCS2_BYTESEQ( "48 89 05 ? ? ? ? 33 D2 66",
		rendersystemdx11.start( ), rendersystemdx11.end( )
	).jump( 0x3 ).as< valve::RenderDeviceDx11 * >( );

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

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Input initialized\n" );
}

void Runtime::initializeRender( ) {
	gRender->initializeAll( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Render initialized\n" );
}

void Runtime::initializeHooks( ) {
	MH_Initialize( );

	auto swapchain = valve::gRenderDeviceDx11->getSwapchain( )->_swapchain;
	
	if ( const auto res = _LLCS2_HOOK( _LLCS2_LOOKUP_VMT( swapchain, 8u ), hooks::present, hooks::gOriginalPresent ) )
		_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create IDXGISwapChain::Present hook with a code of %i!\n", res );

	if ( const auto res = _LLCS2_HOOK( _LLCS2_LOOKUP_VMT( swapchain, 13u ), hooks::resizeBuffers, hooks::gOriginalResizeBuffers ) )
		_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create IDXGISwapChain::ResizeBuffers hook with a code of %i!\n", res );

	MH_EnableHook( MH_ALL_HOOKS );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Hooks initialized\n" );
}

void performTests( ) {
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | DXGI Swapchain at %p\n", valve::gRenderDeviceDx11->getSwapchain( )->_swapchain );
}

void Runtime::initializeWorkers( ) {
	attachConsole( );

	extractModuleData( );

	findAuxAddresses( );

	performTests( );

	initializeInput( );

	initializeRender( );

	initializeHooks( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Initialization finished\n" );

	for ( ; true; )
		std::this_thread::sleep_for( std::chrono::seconds{ 1u } );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Exiting\n" );

	detachConsole( );
}