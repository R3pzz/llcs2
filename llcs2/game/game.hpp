#pragma once

#include <toolkit/toolkit.hpp>

#define _LLCS2_HOOK( Target, Replace, Original ) \
MH_CreateHook( Target.as< LPVOID >( ), \
	reinterpret_cast< LPVOID >( Replace ), \
	reinterpret_cast< LPVOID * >( &Original ) \
)

#define _LLCS2_LOOKUP_VMT( Thisptr, Index ) ( *Mem{ Thisptr }.as< Mem ** >( ) )[ Index ]

#define _LLCS2_INTERFACE( Declaration, Convention, Index, ... ) \
inline auto Declaration { \
	return ( *Mem{ this }.as< Mem ** >( ) )[ Index ] \
		.as< Convention >( )( this, __VA_ARGS__ ); \
}

#define _LLCS2_BUILD_CONV( Result, ... ) Result( __thiscall * )( decltype( this ), __VA_ARGS__ )

#define _LLCS2_CALL_VIA_ADDR( Declaration, Convention, Address, ... ) \
inline auto Declaration { \
	return Address.as< Convention >( )( this, __VA_ARGS__ ); \
}

#define _LLCS2_OFFSET_F( Name, Type, Offset ) \
inline std::add_lvalue_reference_t< Type > Name { \
	return *Mem{ this }.offset( Offset ).as< Type* >( ); \
}

#define _LLCS2_SCHEMA_F( Name, Type, Field ) \
inline std::add_lvalue_reference_t< Type > Name { \
	return *Mem{ this }.offset( _runtime->getOffset( _( Field ) ) ).as< Type* >( ); \
}

#define _LLCS2_SCHEMA_F_PTR( Name, Type, Field ) \
inline std::add_pointer_t< Type > Name { \
	return Mem{ this }.offset( _runtime->getOffset( _( Field ) ) ).as< Type* >( ); \
}

#include "input/hotkeysys.hpp"
#include "input/inputsys.hpp"

#include "render/font.hpp"
#include "render/rendersys.hpp"

#include "runtime/configsys.hpp"
#include "runtime/runtime.hpp"

#include "valve/misc.hpp"
#include "valve/classes.hpp"
#include "valve/interfaces.hpp"

#include "hooks/hooks.hpp"

#include "hacks/information/interface/uisys.hpp"
#include "hacks/information/game/espsys.hpp"
#include "hacks/scene/models/modelsys.hpp"