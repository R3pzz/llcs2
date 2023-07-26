#pragma once

inline constexpr glm::vec2 BoundingBox::getOrigin( ) const {
	return { x, z };
}

inline constexpr glm::vec2 BoundingBox::getExtent( ) const {
	return { y - x, w - z };
}

inline constexpr float BoundingBox::getWidth( ) const {
	return y - x;
}

inline constexpr float BoundingBox::getHeight( ) const {
	return w - z;
}

inline constexpr glm::vec2 BoundingBox::getTopLeft( ) const {
	return { x, z };
}

inline constexpr glm::vec2 BoundingBox::getTopRight( ) const {
	return { y, z };
}

inline constexpr glm::vec2 BoundingBox::getBottomLeft( ) const {
	return { x, w };
}

inline constexpr glm::vec2 BoundingBox::getBottomRight( ) const {
	return { y, w };
}

inline constexpr bool BoundingBox::isValid( ) const {
	return x || y || z || w;
}

inline constexpr bool BoundingBox::operator!( ) const {
	return !x && !y && !z && !w;
}