#pragma once

/**
* Font system.
* 1. Renderer instance will have the font registry, which will store all known fonts.
* 2. Font encapsulates the text rendering API. ImGui is the low-level library for rendering.
* 3. To render a text, we'll need to get the desired font from the library and then use it
*			as an API to render the text.
*/

struct Font {
	/** Font draw type describes the way a text will be rendered */
	enum : std::uint32_t {
		kNone			= 0u,
		kShadowed = 1u,
		kOutlined	= 2u,
	};

	/**
	* Font position flags describe the way text position will be constrained.
	* 
	*					Left	 Middle	 Right
	*					 |			 |			 |
	* Top	-----*-------*-------*
	*					 |			 |			 |
	* Center --*-------*-------*
	* 				 |			 |			 |
	* Bottom --*-------*-------*
	*/
	enum : std::uint32_t {
		kTop			= 1u << 0u,
		kCenter		= 1u << 1u,
		kBottom		= 1u << 2u,
		kLeft			= 1u << 3u,
		kMiddle		= 1u << 4u,
		kRight		= 1u << 5u,
		kDefault	= kTop | kLeft,
	};

	static constexpr glm::vec4 ShadowColor = { .3f, .3f, .3f, .7f };
	static constexpr glm::vec4 OutlineColor = { .1f, .1f, .1f, 1.f };

	ImFont					*_imguiFont{};
	std::uint32_t		_drawType{};
	float						_size{};

	inline constexpr Font( ) = default;

	inline constexpr Font( ImFont *imgui_font, const std::uint32_t draw_type, const float size )
		: _imguiFont{ imgui_font }, _drawType{ draw_type }, _size{ size } { }

	inline glm::vec2 getTextSize( const std::string_view text ) const;

	bool fromTtf( const std::string_view dir,
		const std::uint32_t draw_type, const float size
	);
	
	void drawText( const std::string_view text,
		const glm::vec2 &pos, const std::uint32_t pos_flags,
		const glm::vec4 &col
	) const;
};

#include "font.inline.inl"