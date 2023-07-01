#pragma once

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
inline constexpr bool Bitfield< _MyBase >::at(
	const std::size_t bit
) const {
	const auto mask = 2 << bit;

	return _base & mask;
}

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
inline constexpr void Bitfield< _MyBase >::set(
	const std::size_t bit, const bool state
) const {
	const auto mask = 2 << bit;

	if ( state == true )
		_base |= mask;
	else
		_base &= ~mask;
}