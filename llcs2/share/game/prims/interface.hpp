#pragma once

#define _V_INTERFACE( body, conv, lookup, ... ) \
inline auto body { \
	return ( *Address{ this }.as<Address **>( ) )[ lookup ] \
		.as<conv>( )( this, __VA_ARGS__ ); \
}

#define _V_CONV_FOR( ret, ... ) ret( __thiscall * )( decltype( this ), __VA_ARGS__ )

namespace game {
	/* interfaces (virtual classes that explicitly share their vtable)
		 are stored in a registry, which is itself accessed through
		 CreateInterface export of each module. this can be exploited
		 by us to obtain the access to some of the game subsystems without
		 the use of pattern-scanning. */
	struct InterfaceDesc {
		using Getter = Address( __cdecl * )( );

		Getter					_getter{};
		const char			*_name{};
		InterfaceDesc		*_next{};

		inline constexpr InterfaceDesc( ) = default;

		inline InterfaceDesc( const InterfaceDesc *other )
			: _getter{ other->_next->_getter },
				_name{ other->_next->_name },
				_next{ other->_next->_next }
		{}

		template <class _Target>
			requires std::is_pointer_v<_Target>
		inline _Target get( ) const;

		template <class _Type>
			requires std::is_pointer_v<_Type>
		inline _Type try_find( const std::string_view name ) const;

		inline static InterfaceDesc *first( const x64::ImageDesc &image );
	};
}

#include "interface.inline.inl"