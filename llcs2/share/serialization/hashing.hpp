#pragma once

#define _HASH_CT( str ) [ ]( ) { constexpr auto res = hash( str ); return res; }( )

inline constexpr std::size_t hash( const char *str );

inline constexpr std::size_t hash( const wchar_t *str );

#include "hashing.inline.inl"