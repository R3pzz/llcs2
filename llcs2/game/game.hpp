#pragma once

#include <toolkit/toolkit.hpp>

#define _LLCS2_INTERFACE( Declaration, Convention, Index, ... ) \
inline auto Declaration { \
	return ( *Mem{ this }.as< Mem ** >( ) )[ Index ] \
		.as< Convention >( )( this, __VA_ARGS__ ); \
}

#define _LLCS2_BUILD_CONV( Result, ... ) Result( __thiscall * )( decltype( this ), __VA_ARGS__ )

#define _LLCS_CALL_VIA_ADDR( Declaration, Convention, Address, ... ) \
inline auto Declaration { \
	return Address.as< Convention >( )( this, __VA_ARGS__ ); \
}

#define _LLCS2_OFFSET_F( Name, Type, Offset ) \
inline std::add_lvalue_reference_t< Type > Name { \
	return *Mem{ this }.offset( Offset ).as< Type* >( ); \
}

#include "input/hotkeysys.hpp"
#include "input/inputsys.hpp"

#include "runtime/runtime.hpp"

#include "valve/misc.hpp"
#include "valve/game.hpp"
#include "valve/interfaces.hpp"