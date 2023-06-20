#pragma once

#define _DEF_CTOR_BASE( obj, ref, op ) inline constexpr obj( ref ) = op;

#define _DEF_ASSIGN_BASE( obj, ref, op ) inline constexpr obj &operator=( ref ) = op;

#define NO_COPY( obj ) \
	_DEF_CTOR_BASE( obj, const obj &, delete ); \
	_DEF_ASSIGN_BASE( obj, const obj &, delete );

#define NO_MOVE( obj ) \
	_DEF_CTOR_BASE( obj, obj &&, delete ); \
	_DEF_ASSIGN_BASE( obj, obj &&, delete );

#include <functional>
#include <thread>
#include <type_traits>
#include <windows.h>
#include <winternl.h>

#include "misc/bitfld.hpp"

#include "mem/ptr.hpp"
#include "mem/os.hpp"