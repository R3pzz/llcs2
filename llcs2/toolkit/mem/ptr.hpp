#pragma once

namespace detail {
	template < typename _MyBase >
		requires std::is_integral_v< _MyBase >
			&& ( sizeof( _MyBase ) >= 2u )
	struct ptr_base_t {
		static constexpr auto k_my_size = sizeof( _MyBase );

		using base_type = _MyBase;
		using diff_type = std::ptrdiff_t;
		using friend_type = ptr_base_t< _MyBase >;

		inline constexpr ptr_base_t( ) = default;

		inline constexpr ptr_base_t(
			ptr_base_t< _MyBase > && ) = default;

		inline constexpr ptr_base_t(
			const ptr_base_t< _MyBase > & ) = default;

		inline constexpr ptr_base_t< _MyBase > &operator=(
			ptr_base_t< _MyBase > && ) = default;

		inline constexpr ptr_base_t< _MyBase > &operator=(
			const ptr_base_t< _MyBase > & ) = default;

		inline constexpr ptr_base_t(
			const base_type imm )
			: m_base{ imm }
		{}

		inline constexpr ptr_base_t(
			const void *ptr )
			: m_base{ reinterpret_cast<_MyBase>( ptr ) }
		{}

		inline constexpr ptr_base_t(
			const std::nullptr_t nullp )
			: m_base{}
		{}
		
		inline constexpr auto offset(
			const diff_type amt ) const;

		inline auto jump(
			const diff_type base_off = 0ll ) const;

		inline auto deref(
			const std::size_t depth = 1ull ) const;

		template < typename _Target >
			requires std::is_pointer_v< _Target >
		inline auto as( ) const;

		template < typename _Target >
			requires std::is_pointer_v< _Target >
		inline constexpr auto &swap_cont(
			const friend_type &with ) const;
			
		inline constexpr auto &swap(
			friend_type &with );

		base_type	m_base{};
	};
}

using ptr_t = detail::ptr_base_t< std::uintptr_t >;
using jmp_t = detail::ptr_base_t< std::uint32_t >;

#include "ptr.inline.inl"