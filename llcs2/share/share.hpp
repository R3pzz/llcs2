#pragma once

#include <array>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>
#include <thread>
#include <memory>
#include <functional>
#include <type_traits>
#include <windows.h>
#include <intrin.h>

#define _ALIGN( amount ) __declspec( align( amount ) )

/* just to match the codestyle since WinApi always
	 complains about uint32_t's and DWORD's */
using ulong_t = unsigned long;

#include "serialization/hashing.hpp"

#include "memory/address.hpp"
#include "memory/native.hpp"
#include "memory/bytes.hpp"

#include "game/prims/recv.hpp"
#include "game/prims/interface.hpp"

#include "runtime/runtime.hpp"