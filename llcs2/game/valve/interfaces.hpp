#pragma once

namespace valve {
	class Engine {
	public:
		_LLCS2_INTERFACE( isInGame( ),
			_LLCS2_BUILD_CONV( bool ), 30u );
	} inline *_engine{};

	class NetworkClient {
	public:

	} inline *_networkClient{};

	class InputSystem {
	public:
		_LLCS2_INTERFACE( attach( HWND handle ),
			_LLCS2_BUILD_CONV( void, HWND ), 11u, handle );

		_LLCS2_INTERFACE( detach( HWND handle ),
			_LLCS2_BUILD_CONV( void, HWND ), 12u, handle );

		std::uint8_t		$align0[ 48u ]{};

		std::size_t			_windowCount{};
		HWND *_windowHandles{};
	} inline *_inputSystem{};

	class ResourceService {
	public:

	} inline *_resourceService{};

	class MaterialSystem {
	public:
		_LLCS2_INTERFACE( findOrCreate( const char *name, Material ***out ),
			_LLCS2_BUILD_CONV( Material ***, Material ***, const char * ), 14u, out, name );
	} inline *_materialSystem{};

	class EntitySystem {
	public:
		inline BaseEntity *getEntity( const std::uint32_t idx );

		inline BaseEntity *getEntity( const Handle handle );

		inline EntityIdentity *getIdentity( const std::uint32_t idx );

		inline EntityIdentity *getIdentity( const Handle handle );

		inline void forEachIdentity( const std::function< bool( EntityIdentity * ) > &fn );
	} inline *_entitySystem{};

	class SchemaSystem {
	public:
		_LLCS2_INTERFACE( globalTypeScope( ),
			_LLCS2_BUILD_CONV( SchemaTypeScope * ), 11u );

		_LLCS2_INTERFACE( typeScopeForModule( const char *module ),
			_LLCS2_BUILD_CONV( SchemaTypeScope *, const char * ), 13u, module );
	} inline *_schemaSystem{};

	class RenderDeviceDx11 {
	public:
		inline SwapChainDx11 *getSwapchain( );
	} inline *_renderDevice{};

	inline glm::mat4 *_mvpMatrix{};
}

#include "interfaces.inline.inl"