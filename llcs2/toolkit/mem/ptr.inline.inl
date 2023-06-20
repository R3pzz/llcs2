#pragma once

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto detail::ptr_base_t< _MyBase >::offset( const diff_type amt ) const {
	return friend_type{ m_base + amt };
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline auto detail::ptr_base_t< _MyBase >::jump( const diff_type base_off ) const {
	return offset( *offset( base_off ).as< std::uint32_t * >( ) );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline auto detail::ptr_base_t< _MyBase >::deref( const std::size_t depth ) const {
	if ( !depth )
		return *this;

	m_base = *as< base_type * >( );

	return deref( depth - 1ull );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
template < typename _Target >
	requires std::is_pointer_v< _Target >
inline auto detail::ptr_base_t< _MyBase >::as( ) const {
	return reinterpret_cast< _Target >( m_base );
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
template < typename _Target >
	requires std::is_pointer_v< _Target >
inline constexpr auto &detail::ptr_base_t< _MyBase >::swap_cont( const friend_type &with ) const {
	_Target buf{};
	
	*with.as< _Target >( ) = *as< _Target >( );
	*as< _Target >( ) = buf;

	return *this;
}

template < typename _MyBase >
	requires std::is_integral_v< _MyBase >
		&& ( sizeof( _MyBase ) >= 2u )
inline constexpr auto &detail::ptr_base_t< _MyBase >::swap( friend_type &with ) {
	std::swap( m_base, with.m_base );

	return *this;
}