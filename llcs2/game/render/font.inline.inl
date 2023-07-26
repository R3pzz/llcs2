#pragma once

inline glm::vec2 Font::getTextSize( const std::string_view text ) const {
	if ( text.empty( )
		|| !_imguiFont )
		return {};

	constexpr auto flt_max = std::numeric_limits< float >::max( );

	const auto vec = _imguiFont->CalcTextSizeA( _size, flt_max, 0.f, text.data( ) );

	return { vec.x, vec.y };
}