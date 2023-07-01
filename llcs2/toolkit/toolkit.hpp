#pragma once

#define _LLCS2_DEF_CTOR_BASE( Class, Operand, Operation ) inline constexpr Class( Operand ) = Operation;

#define _LLCS2_DEF_ASSIGN_BASE( Class, Operand, Operation ) inline constexpr Class &operator=( Operand ) = Operation;

#define _LLCS2_NO_COPY( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, const Class &, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, const Class &, delete );

#define _LLCS2_NO_MOVE( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, Class &&, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, Class &&, delete );

#define _LLCS2_INTERFACE( Declaration, Convention, Index, ... ) \
inline auto Declaration { \
	return ( *Mem{ this }.as< Mem ** >( ) )[ Index ] \
		.as< Convention >( )( this, __VA_ARGS__ ); \
}

#define _LLCS2_INTERF_CONV( Result, ... ) Result( __thiscall * )( decltype( this ), __VA_ARGS__ )

#define _LLCS2_BYTESEQ( String, Start, End ) ByteSequence< ByteString::bytenum( String ) >{ ByteString{ String } }.seek( Start, End )

#include <algorithm>
#include <array>
#include <functional>
#include <thread>
#include <type_traits>
#include <windows.h>
#include <winternl.h>

#include "misc/hash.hpp"
#include "misc/bitfld.hpp"
#include "misc/strings.hpp"

#include "mem/mem.hpp"
#include "mem/bytes.hpp"
#include "mem/os.hpp"

#include "valve/misc.hpp"
#include "valve/game.hpp"
#include "valve/interfaces.hpp"