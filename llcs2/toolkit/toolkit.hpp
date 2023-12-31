#pragma once

#define _LLCS2_DEF_CTOR_BASE( Class, Operand, Operation ) inline constexpr Class( Operand ) = Operation;

#define _LLCS2_DEF_ASSIGN_BASE( Class, Operand, Operation ) inline constexpr Class &operator=( Operand ) = Operation;

#define _LLCS2_NO_COPY( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, const Class &, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, const Class &, delete );

#define _LLCS2_NO_MOVE( Class ) \
	_LLCS2_DEF_CTOR_BASE( Class, Class &&, delete ); \
	_LLCS2_DEF_ASSIGN_BASE( Class, Class &&, delete );

#define _LLCS2_ENUM_OPS( Enum ) \
inline constexpr auto operator-( const Enum val ) { \
	return static_cast< std::underlying_type_t< Enum > >( val ); \
} \
 \
inline constexpr auto operator|( const Enum rhs, const Enum lhs ) { \
	return static_cast< Enum >( -rhs | -lhs ); \
}

#define _LLCS2_BYTESEQ( String, Start, End ) ByteSequence< ByteString::bytenum( String ) >{ ByteString{ String } }.seek( Start, End )

#ifndef _LLCS2_DISABLE_LOG
#define _LLCS2_DISABLE_LOG 1
#endif

#if _DEBUG && !_LLCS2_DISABLE_LOG
#define _LLCS2_LOG( What, ... ) std::printf( What, __VA_ARGS__ )
#define _LLCS2_LOG_F( What, ... ) std::fprintf( _runtime->getLogOut( ), What, __VA_ARGS__ )
#else
#define _LLCS2_LOG( What, ... )
#define _LLCS2_LOG_F( Where, What, ... )
#endif

#if _DEBUG
#define _LLCS2_LOG_IMPORTANT( What, ... ) std::printf( What, __VA_ARGS__ )
#define _LLCS2_LOG_IMPORTANT_F( What, ... ) std::fprintf( _runtime->getLogOut( ), What, __VA_ARGS__ )
#else
#define _LLCS2_LOG_IMPORTANT( What, ... )
#define _LLCS2_LOG_IMPORTANT_F( Where, What, ... )
#endif

#define IM_VEC2_CLASS_EXTRA \
inline constexpr ImVec2( const glm::vec2 &vec ) \
	: x{ vec.x }, y{ vec.y } {}

#define IM_VEC4_CLASS_EXTRA \
inline constexpr ImVec4( const glm::vec4 &vec ) \
	: x{ vec.x }, y{ vec.y }, z{ vec.z }, w{ vec.w } {}

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <functional>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <type_traits>
#include <dxgi.h>
#include <d3d11.h>
#include <windows.h>
#include <winternl.h>
#include <shlobj.h>

#include <thirdparty/glm/glm.hpp>

#include <thirdparty/json/json.hpp>

#include <thirdparty/imgui/imgui.h>
#include <thirdparty/imgui/imgui_internal.h>
#include <thirdparty/imgui/backends/imgui_impl_dx11.h>
#include <thirdparty/imgui/backends/imgui_impl_win32.h>

#include <thirdparty/minhook/minhook.h>

#include "math/math.hpp"

#include "misc/hash.hpp"
#include "misc/bitfld.hpp"
#include "misc/strings.hpp"

#include "config/config.hpp"

#include "mem/mem.hpp"
#include "mem/bytes.hpp"
#include "mem/os.hpp"