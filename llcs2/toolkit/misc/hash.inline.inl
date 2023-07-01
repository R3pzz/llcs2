#pragma once

template < typename _CharType >
	requires std::_Is_any_of_v<
		_CharType, char, wchar_t >
inline constexpr std::size_t hash( const _CharType * str ) {
	constexpr auto k_prime = 0x100000001b3ull;

	auto basis = 0xcbf29ce484222325ull;

	for ( std::size_t i{}; str[ i ] != '\0'; i++ ) {
		basis ^= str[ i ];
		basis *= k_prime;
	}

	return basis;
}