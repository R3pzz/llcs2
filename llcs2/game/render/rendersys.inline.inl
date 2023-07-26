#pragma once

inline Font &RenderSystem::getFont( const std::size_t name ) {
	return _fontTable.at( name );
}

inline void RenderSystem::pushRectangle( const glm::vec2 &pos, const glm::vec2 &extent,
	const glm::vec4 &col, const bool outline, const bool opaque, const float roundness
) {
	const auto col32 = ImGui::ColorConvertFloat4ToU32( col );
	const auto outline_col32 = ImGui::ColorConvertFloat4ToU32( { 0.f, 0.f, 0.f, 1.f } );

	if ( outline ) {
		ImGui::GetBackgroundDrawList( )->AddRect( pos - glm::vec2{ 1.f, 1.f },
			pos + extent + glm::vec2{ 2.f, 2.f }, outline_col32, roundness
		);

		ImGui::GetBackgroundDrawList( )->AddRect( pos + glm::vec2{ 1.f, 1.f },
			pos + extent - glm::vec2{ 2.f, 2.f }, outline_col32, roundness
		);
	}

	if ( opaque )
		ImGui::GetBackgroundDrawList( )->AddRectFilled( pos, pos + extent, col32, roundness );
	else
		ImGui::GetBackgroundDrawList( )->AddRect( pos, pos + extent, col32, roundness );
}

inline void RenderSystem::pushFadeRectangle( const glm::vec2 &pos, const glm::vec2 &extent,
	const GradientMap &col, const bool opaque
) {

}