#pragma once

namespace detail {
	template < typename _MyBase >
		requires std::is_integral_v< _MyBase >
			&& ( sizeof( _MyBase ) >= 2u )
	struct BaseMem {
		typedef
			_MyBase
			BaseType;

		typedef
			std::ptrdiff_t
			DiffType;

		typedef
			BaseMem< _MyBase >
			FriendType;

		inline constexpr BaseMem( ) = default;

		inline constexpr BaseMem( const BaseType imm )
			: _base{ imm }
		{}

		inline constexpr BaseMem( const void *ptr )
			: _base{ reinterpret_cast<_MyBase>( ptr ) }
		{}

		inline constexpr BaseMem( const std::nullptr_t )
			: _base{}
		{}

		inline constexpr auto offset( const DiffType amt ) const;

		inline auto jump( const DiffType base_off = 0ll ) const;

		inline auto deref( const std::size_t depth = 1ull ) const;

		template < typename _Target >
			requires std::is_pointer_v< _Target >
		inline auto as( ) const;

		template < typename _Target >
			requires std::is_pointer_v< _Target >
		inline constexpr auto &swapCont( const FriendType &with ) const;

		inline constexpr auto &swap( FriendType &with );

		inline constexpr auto operator+( const DiffType v ) const;

		inline constexpr auto operator-( const DiffType v ) const;

		inline constexpr auto operator*( const DiffType v ) const;

		inline constexpr auto operator/( const DiffType v ) const;

		inline constexpr auto operator<( const FriendType &other ) const;

		inline constexpr auto operator>( const FriendType &other ) const;

		inline constexpr auto operator<=( const FriendType &other ) const;

		inline constexpr auto operator>=( const FriendType &other ) const;

		inline constexpr auto operator!( ) const;

		inline constexpr auto &operator++( );

		inline constexpr auto &operator++( int );

		inline constexpr auto &operator--( );

		inline constexpr auto &operator--( int );

		BaseType	_base{};
	};
}

using Mem = detail::BaseMem< std::uintptr_t >;
using Jump = detail::BaseMem< std::uint32_t >;

#include "mem.inline.inl"