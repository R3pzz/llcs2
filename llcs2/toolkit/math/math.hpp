#pragma once

struct BoundingBox : glm::vec4 {
	/**
	* x - left;
	* y - right;
	* z - top;
	* w - bottom;
	*/

	inline constexpr BoundingBox( ) = default;

	inline constexpr BoundingBox( const glm::vec4 &vec )
		: glm::vec4{ vec } {}

	inline constexpr BoundingBox( const glm::vec2 &pos, const glm::vec2 &extent )
		: glm::vec4{ pos, extent } {}

	inline constexpr BoundingBox( const float left, const float top, const float right, const float bottom )
		: glm::vec4{ left, right, top, bottom } {}

	inline constexpr glm::vec2 getOrigin( ) const;

	inline constexpr glm::vec2 getExtent( ) const;

	inline constexpr float getWidth( ) const;

	inline constexpr float getHeight( ) const;

	inline constexpr glm::vec2 getTopLeft( ) const;

	inline constexpr glm::vec2 getTopRight( ) const;

	inline constexpr glm::vec2 getBottomLeft( ) const;

	inline constexpr glm::vec2 getBottomRight( ) const;

	inline constexpr bool isValid( ) const;

	inline constexpr bool operator!( ) const;
};

#include "math.inline.inl"