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
	const auto scope = valve::_schemaSystem->typeScopeForModule( module.data( ) );
	if ( !scope )
		return;

	const auto bindings = &scope->_bindings;

	_LLCS2_LOG_F( "[SchemaWalk] | Binding table for a module %s: %p, size: %i\n",
		module.data( ), bindings, bindings->_size
	);

	bindings->forEachElement(
		[ scope, &out ]( valve::SchemaTypeScope::ClassBinding *binding ) {
			if ( !binding )
				return true;

			_LLCS2_LOG_F( "  [SchemaWalk] | Found a class (name: %s, at: %p)\n",
				binding->_name, binding
			);

			for ( std::uint16_t i{}; i < binding->_fieldSize; i++ ) {
				auto &field = binding->_fields[ i ];

				char str[ 512u ]{};

				std::strcpy( str, binding->_name );
				std::strcat( str, "." );
				std::strcat( str, field._name );
				std::strcat( str, "\0" );

				_LLCS2_LOG_F( "    [SchemaWalk] | Found a field (name: %s, type: %s, offset: %u, at: %p, hash: %zu)\n",
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

	valve::_engine = _knownInterfaces.at( _( "Source2EngineToClient001" ) ).as< valve::Engine * >( );

	valve::_resourceService = _knownInterfaces.at( _( "GameResourceServiceClientV001" ) ).as< valve::ResourceService * >( );

	valve::_materialSystem = _knownInterfaces.at( _( "VMaterialSystem2_001" ) ).as< valve::MaterialSystem * >( );

	valve::_entitySystem = *Mem{ valve::_resourceService }.offset( 0x58 ).as< valve::EntitySystem ** >( );

	valve::_inputSystem = _knownInterfaces.at( _( "InputSystemVersion001" ) ).as< valve::InputSystem * >( );

	valve::_schemaSystem = _knownInterfaces.at( _( "SchemaSystem_001" ) ).as< valve::SchemaSystem * >( );

	valve::_networkClient = _LLCS2_BYTESEQ( "48 8B 1D ? ? ? ? 48 8B F9 48 8B CB",
		engine.start( ), engine.end( )
	).jump( 0x3 ).as< valve::NetworkClient * >( );

	valve::_renderDevice = _LLCS2_BYTESEQ( "48 89 05 ? ? ? ? 33 D2 66",
		rendersystemdx11.start( ), rendersystemdx11.end( )
	).jump( 0x3 ).as< valve::RenderDeviceDx11 * >( );

	valve::_mvpMatrix = _LLCS2_BYTESEQ( "48 8D 0D ? ? ? ? 48 C1 E0 06",
		client.start( ), client.end( )
	).jump( 0x3 ).as< glm::mat4 * >( );

	ldr->forEachInLoadEntry(
		[ this ]( os::LdrEntry *entry ) {
			extractSchemaData( toNarrow( entry->_baseDllName.wstr( ) ),
				_knownOffsets
			);

			return false;
		}
	);

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Module data extracted\n" );
}

void Runtime::findAuxAddresses( ) {
	const auto client = _knownModules.at( _( "client.dll" ) );
	const auto materialsystem = _knownModules.at( _( "materialsystem2.dll" ) );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Addresses found\n" );
}

void Runtime::initializeInput( ) {
	_inputSystem->initializeAll( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Input initialized\n" );
}

void Runtime::initializeRender( ) {
	_renderSystem->initializeAll( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Render initialized\n" );
}

void Runtime::cacheDefaultConfig( ) {
	_defaultConfig = new Config{ "config.cfg" };
}

void Runtime::initializeHooks( ) {
	MH_Initialize( );

	const auto client = _knownModules.at( _( "client.dll" ) );
	const auto scenesystem = _knownModules.at( _( "scenesystem.dll" ) );

	{
		const auto addr = _LLCS2_BYTESEQ( "48 89 5C 24 ? 56 48 83 EC 30 8B 05 ? ? ? ? 8D 5A FF 3B C2 48 8B F1 48 8B",
			client.start( ), client.end( )
		);
		
		if ( const auto res = _LLCS2_HOOK( addr, hooks::frameStageNotify, hooks::_originalFrameStageNotify ) )
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create CHLClient::FrameStageNotify hook with a code of %i!\n", res );
	}

	{
		auto swapchain = valve::_renderDevice->getSwapchain( )->_swapchain;

		if ( const auto res = _LLCS2_HOOK( _LLCS2_LOOKUP_VMT( swapchain, 8u ), hooks::present, hooks::_originalPresent ) )
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create IDXGISwapChain::Present hook with a code of %i!\n", res );

		if ( const auto res = _LLCS2_HOOK( _LLCS2_LOOKUP_VMT( swapchain, 13u ), hooks::resizeBuffers, hooks::_originalResizeBuffers ) )
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create IDXGISwapChain::ResizeBuffers hook with a code of %i!\n", res );
	}

	{
		const auto addr = _LLCS2_BYTESEQ( "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 49 8B 41",
			scenesystem.start( ), scenesystem.end( )
		);

		if ( const auto res = _LLCS2_HOOK( addr, hooks::getMaterialForDraw, hooks::_originalGetMaterialForDraw ) )
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Failed to create CBaseSceneObjectDesc::GetMaterialForDraw hook with a code of %i!\n", res );
	}

	MH_EnableHook( MH_ALL_HOOKS );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Hooks initialized\n" );
}

void performTests( ) {
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Entity system at %p\n", valve::_entitySystem );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Engine at %p\n", valve::_engine );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Network client at %p\n", valve::_networkClient );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Resource service at %p\n", valve::_resourceService );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | DXGI swapchain at %p\n", valve::_renderDevice->getSwapchain( )->_swapchain );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | MVP matrix at %p\n", valve::_mvpMatrix );
	_LLCS2_LOG_IMPORTANT( "[Main Thread] | hooks::getMaterialForDraw at %p\n", &hooks::getMaterialForDraw );
}

void Runtime::initializeWorkers( ) {
	attachConsole( );

	extractModuleData( );

	findAuxAddresses( );

	performTests( );

	initializeInput( );

	initializeRender( );

	cacheDefaultConfig( );

	initializeHooks( );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Initialization finished\n" );

	for ( ; true; )
		std::this_thread::sleep_for( std::chrono::seconds{ 1u } );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Exiting\n" );

	detachConsole( );
}