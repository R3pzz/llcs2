#pragma once

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::offset(
	const DiffType amt
) const {
	return FriendType{ _base + amt };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline auto detail::BaseMem< _MyBase >::jump(
	const DiffType base_off
) const {
	return offset( *offset( base_off ).as< std::int32_t * >( ) + 0x4 + base_off );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline auto detail::BaseMem< _MyBase >::deref(
	const std::size_t depth
) const {
	if ( !depth )
		return *this;

	_base = *as< BaseType * >( );

	return deref( depth - 1ull );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
template < typename _Target >
	requires std::is_pointer_v< _Target >
inline auto detail::BaseMem< _MyBase >::as( ) const {
	return reinterpret_cast< _Target >( _base );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
template < typename _Target >
	requires std::is_pointer_v< _Target >
inline constexpr auto &detail::BaseMem< _MyBase >::swapCont(
	const FriendType &with
) const {
	_Target buf{};
	
	*with.as< _Target >( ) = *as< _Target >( );
	*as< _Target >( ) = buf;

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::BaseMem< _MyBase >::swap(
	FriendType &with
) {
	std::swap( _base, with._base );

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator+(
	const DiffType v
) const {
	return detail::BaseMem< _MyBase >{ _base + v };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator-(
	const DiffType v
) const {
	return detail::BaseMem< _MyBase >{ _base - v };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator*(
	const DiffType v
) const {
	return detail::BaseMem< _MyBase >{ _base *v };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator/(
	const DiffType v
) const {
	return detail::BaseMem< _MyBase >{ _base / v };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator<(
	const FriendType &other
) const {
	return _base < other._base;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator>(
	const FriendType &other
) const {
	return _base > other._base;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator<=(
	const FriendType &other
) const {
	return _base <= other._base;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator>=(
	const FriendType &other
) const {
	return _base >= other._base;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::BaseMem< _MyBase >::operator!( ) const {
	return !_base;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::BaseMem< _MyBase >::operator++( ) {
	_base++;

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::BaseMem< _MyBase >::operator++( int ) {
	++_base;

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::BaseMem< _MyBase >::operator--( ) {
	_base--;

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::BaseMem< _MyBase >::operator--( int ) {
	--_base;

	return *this;
}