#pragma once

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
inline constexpr bool bitfield_t< _MyBase >::at( const std::size_t bit ) const {
	const auto mask = 2 << bit;

	return m_base & mask;
}

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
inline constexpr void bitfield_t< _MyBase >::set( const std::size_t bit, const bool state ) const {
	const auto mask = 2 << bit;

	if ( state == true )
		m_base |= mask;
	else
		m_base &= ~mask;
}