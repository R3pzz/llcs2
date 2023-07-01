#pragma once

#define _( str ) [ ]( ) { constexpr auto result = hash( str ); return result; }( )

template < typename _CharType >
	requires std::_Is_any_of_v<
		_CharType, char, wchar_t >
inline constexpr std::size_t hash(
	const _CharType * str
);

#include "hash.inline.inl"