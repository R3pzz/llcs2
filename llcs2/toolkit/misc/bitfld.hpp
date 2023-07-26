#pragma once

template < typename _MyBase >
	requires std::is_arithmetic_v< _MyBase >
struct Bitfield {
	typedef
		_MyBase
		BaseType;

	inline constexpr Bitfield( ) = default;

	inline constexpr Bitfield( const _MyBase base )
		: _base{ base }
	{}

	inline constexpr bool at(
		const std::size_t bit
	) const;

	inline constexpr void set(
		const std::size_t bit, const bool state
	) const;

	BaseType _base{};
};

#include "bitfld.inline.inl"