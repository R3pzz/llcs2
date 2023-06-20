#pragma once

inline constexpr std::size_t hash( const char *str ) {
	constexpr auto Basis = 0xcbf29ce484222325u;
	constexpr auto Prime = 0x100000001b3u;

	std::size_t result{};

	for ( std::size_t i{}; str[ i ] != '\0'; i++ ) {
		result ^= str[ i ];
		result *= Prime;
	}

	return result;
}

inline constexpr std::size_t hash( const wchar_t *str ) {
	constexpr auto Basis = 0xcbf29ce484222325u;
	constexpr auto Prime = 0x100000001b3u;

	std::size_t result{};

	for ( std::size_t i{}; str[ i ] != '\0'; i++ ) {
		result ^= str[ i ];
		result *= Prime;
	}

	return result;
}