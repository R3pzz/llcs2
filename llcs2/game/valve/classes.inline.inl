#pragma once

template < typename _CastType >
inline constexpr _CastType *valve::EntityInstance::as( ) {
	return reinterpret_cast< _CastType * >( this );
}

template < typename _CastType >
inline constexpr const _CastType *valve::EntityInstance::as( ) const {
	return reinterpret_cast< const _CastType * >( this );
}

inline glm::vec4 valve::BaseEntity::healthAsColor( ) {
	return getHealth( ) >= 66
		? glm::vec4{ 0.f, 1.f, 0.f, 1.f }
		: ( getHealth( ) <= 33
		? glm::vec4{ 1.f, 0.f, 0.f, 1.f }
		: glm::vec4{ 1.f, 1.f, 0.f, 1.f } );
}