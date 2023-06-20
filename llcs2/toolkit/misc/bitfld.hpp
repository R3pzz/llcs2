#pragma once

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
struct bitfield_t {
	using base_type = _MyBase;

	inline constexpr bitfield_t( ) = default;

	inline constexpr bitfield_t(
		const base_type base )
		: m_base{ base }
	{}

	inline constexpr bool at(
		const std::size_t bit ) const;

	inline constexpr void set(
		const std::size_t bit, const bool state ) const;

	base_type m_base{};
};

#include "bitfld.inline.inl"