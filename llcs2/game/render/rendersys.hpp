#pragma once

struct GradientMap {
	glm::vec4 _topLeft{}, _topRight{},
						_bottomLeft{}, _bottomRight{};

	inline constexpr GradientMap( ) = default;
};

class RenderSystem {
	_LLCS2_NO_COPY( RenderSystem );

	typedef
		std::unordered_map< std::size_t, Font >
		FontTable;

	/** Direct3D 11 related stuff */
	IDXGISwapChain					*_swapchain{};
	ID3D11Device						*_device{};
	ID3D11RenderTargetView	*_renderTarget{};
	ID3D11DeviceContext			*_deviceCtx{};

	/** Is current render context valid? */
	bool										_isValid{};

	/** All the fonts we're using */
	FontTable								_fontTable{};

	/** Recreate the d3d11 context. */
	void recreateContext( );
	/** Destroy the d3d11 context. */
	void destroyContext( );

public:
	inline constexpr RenderSystem( ) = default;

	inline Font &getFont( const std::size_t name );

	inline void pushRectangle( const glm::vec2 &pos, const glm::vec2 &extent,
		const glm::vec4 &col, const bool outline = true, const bool opaque = false, const float roundness = 0.f
	);
	
	inline void pushFadeRectangle( const glm::vec2 &pos, const glm::vec2 &extent,
		const GradientMap &col, const bool opaque = false
	);

	bool projectViewToScreen( const glm::vec3 &view, glm::vec2 &screen );

	void initializeAll( );

	void onPresentPre( IDXGISwapChain *swapchain,
		const std::uint32_t sync, const std::uint32_t flags
	);

	void onPresentPost( IDXGISwapChain *swapchain,
		const std::uint32_t sync, const std::uint32_t flags
	);

	void onResizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
		const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
	);
};

inline auto _renderSystem = std::make_unique< RenderSystem >( );

#include "rendersys.inline.inl"