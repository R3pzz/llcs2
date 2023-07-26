#include <game/game.hpp>

bool Font::fromTtf( const std::string_view dir,
	const std::uint32_t draw_type, const float size
) {
	if ( dir.empty( ) )
		return false;

	ImFontConfig cfg{};

	_imguiFont = ImGui::GetIO( ).Fonts->AddFontFromFileTTF( dir.data( ), size,
		&cfg, ImGui::GetIO( ).Fonts->GetGlyphRangesCyrillic( )
	);

	if ( !_imguiFont )
		return false;

	_drawType = draw_type;
	_size = size;

	return true;
}

void Font::drawText( const std::string_view text,
	const glm::vec2 &pos, const std::uint32_t pos_flags,
	const glm::vec4 &col
) const {
	/** Runaround to simplify the imgui calls... */
	auto pushTextInternal = [ this ]( const std::string_view text, const glm::vec2 &pos, const glm::vec4 &col ) {
		ImGui::GetBackgroundDrawList( )->AddText( _imguiFont, _size, { pos.x, pos.y },
			ImGui::ColorConvertFloat4ToU32( { col.r, col.g, col.b, col.a } ), text.data( )
		);
	};

	if ( text.empty( ) )
		return;

	auto transformed = pos;

	const auto size = getTextSize( text );

	if ( pos_flags & kRight )
		transformed.x -= size.x;
	else if ( pos_flags & kMiddle )
		transformed.x -= size.x * .5f;

	if ( pos_flags & kBottom )
		transformed.y -= size.y;
	else if ( pos_flags & kCenter )
		transformed.y -= size.y * .5f;

	switch ( _drawType ) {
	case kShadowed: {
		pushTextInternal( text, transformed + glm::vec2{ 0.f, 1.f }, ShadowColor );

		break;
	}
	case kOutlined: {
		pushTextInternal( text, transformed + glm::vec2{ 1.f, 1.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ 1.f, -1.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ -1.f, 1.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ -1.f, -1.f }, OutlineColor );

		pushTextInternal( text, transformed + glm::vec2{ 0.f, 1.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ 0.f, -1.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ 1.f, 0.f }, OutlineColor );
		pushTextInternal( text, transformed + glm::vec2{ -1.f, 0.f }, OutlineColor );

		break;
	}
	default:
		break;
	}

	pushTextInternal( text, transformed, col );
}