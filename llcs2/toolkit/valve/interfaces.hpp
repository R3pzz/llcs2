#pragma once

namespace valve {
	class InputSystem {
	public:
		_LLCS2_INTERFACE( attach( HWND handle ),
			_LLCS2_INTERF_CONV( void, HWND ), 11u, handle );

		_LLCS2_INTERFACE( detach( HWND handle ),
			_LLCS2_INTERF_CONV( void, HWND ), 12u, handle );

		std::uint8_t		$align0[ 48u ]{};

		std::size_t			_windowCount{};
		HWND						*_windowHandles{};
	} inline *gInputSystem{};

	class EntitySystem {
	public:

	} inline *gEntitySystem{};

	class SchemaSystem {
	public:
		_LLCS2_INTERFACE( globalTypeScope( ),
			_LLCS2_INTERF_CONV( SchemaTypeScope * ), 11u );

		_LLCS2_INTERFACE( typeScopeForModule( const char *module ),
			_LLCS2_INTERF_CONV( SchemaTypeScope *, const char * ), 13u, module );
	} inline *gSchemaSystem{};
}