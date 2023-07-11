#pragma once

namespace valve {
	class InputSystem {
	public:
		_LLCS2_INTERFACE( attach( HWND handle ),
			_LLCS2_BUILD_CONV( void, HWND ), 11u, handle );

		_LLCS2_INTERFACE( detach( HWND handle ),
			_LLCS2_BUILD_CONV( void, HWND ), 12u, handle );

		std::uint8_t		$align0[ 48u ]{};

		std::size_t			_windowCount{};
		HWND *_windowHandles{};
	} inline *gInputSystem{};

	class ResourceSystem {
	public:

	} inline *gResourceSystem{};

	class EntitySystem {
	public:
		inline PlayerController *getController( const std::uint32_t idx );

		inline BaseEntity *getEntity( PlayerController *controller );

		inline BaseEntity *getEntity( const std::uint32_t idx );

		inline BaseEntity *getEntity( const Handle handle );
	} inline *gEntitySystem{};

	class SchemaSystem {
	public:
		_LLCS2_INTERFACE( globalTypeScope( ),
			_LLCS2_BUILD_CONV( SchemaTypeScope * ), 11u );

		_LLCS2_INTERFACE( typeScopeForModule( const char *module ),
			_LLCS2_BUILD_CONV( SchemaTypeScope *, const char * ), 13u, module );
	} inline *gSchemaSystem{};

	class RenderDeviceDx11 {
	public:
		inline SwapChainDx11 *getSwapchain( );
	} inline *gRenderDeviceDx11{};
}

#include "interfaces.inline.inl"