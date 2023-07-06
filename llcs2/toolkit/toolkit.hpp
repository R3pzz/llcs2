#pragma once

#define _LLCS2_DEF_CTOR_BASE( Class, Operand, Operation ) inline constexpr Class( Operand ) = Operation;

#define _LLCS2_DEF_ASSIGN_BASE( Class, Operand, Operation ) inline constexpr Class &operator=( Operand ) = Operation;

#define _LLCS2_NO_COPY( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, const Class &, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, const Class &, delete );

#define _LLCS2_NO_MOVE( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, Class &&, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, Class &&, delete );

#define _LLCS2_BYTESEQ( String, Start, End ) ByteSequence< ByteString::bytenum( String ) >{ ByteString{ String } }.seek( Start, End )

#ifndef _LLCS2_DISABLE_LOG
#define _LLCS2_DISABLE_LOG 1
#endif

#if _DEBUG && !_LLCS2_DISABLE_LOG
#define _LLCS2_LOG( What, ... ) std::printf( What, __VA_ARGS__ )
#else
#define _LLCS2_LOG( What, ... )
#endif

#if _DEBUG
#define _LLCS2_LOG_IMPORTANT( What, ... ) std::printf( What, __VA_ARGS__ )
#else
#define _LLCS2_LOG_IMPORTANT( What, ... )
#endif

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