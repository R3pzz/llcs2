#pragma once

namespace detail {
	template <typename _Size>
		requires std::is_integral_v<_Size>
	struct AddressBase {
		template <typename _Type>
		static constexpr bool IsDirectCastable = std::is_integral<_Type>::value;

		using SizeType = _Size;
		using DiffType = std::ptrdiff_t;
		
		SizeType _ptr{};

		inline constexpr AddressBase( ) = default;

		inline constexpr AddressBase( const void *ptr )
			: _ptr{ reinterpret_cast<SizeType>( ptr ) } {}

		inline constexpr AddressBase( const SizeType ptr )
			: _ptr{ ptr } {}

		template <typename _Type>
		inline constexpr auto as( ) const;

		inline constexpr auto &offset_self( const DiffType v );

		inline constexpr auto offset( const DiffType v ) const;

		inline constexpr auto operator+( const DiffType v ) const;

		inline constexpr auto operator-( const DiffType v ) const;

		inline constexpr auto operator*( const DiffType v ) const;

		inline constexpr auto operator/( const DiffType v ) const;

		inline constexpr auto operator<( const AddressBase<SizeType> &other ) const;

		inline constexpr auto operator>( const AddressBase<SizeType> &other ) const;

		inline constexpr auto operator<=( const AddressBase<SizeType> &other ) const;

		inline constexpr auto operator>=( const AddressBase<SizeType> &other ) const;

		inline constexpr auto operator!( ) const;

		inline constexpr auto &operator++( );

		inline constexpr auto &operator++( int );

		inline constexpr auto &operator--( );

		inline constexpr auto &operator--( int );
	};
}

using Address = detail::AddressBase<std::uintptr_t>;
using RelJump = detail::AddressBase<std::uint32_t>;

#include "address.inline.inl"