#pragma once

class RenderSystem {
	_LLCS2_NO_COPY( RenderSystem );

	/** Direct3D 11 related stuff */
	IDXGISwapChain					*_swapchain{};
	ID3D11Device						*_device{};
	ID3D11RenderTargetView	*_renderTarget{};
	ID3D11DeviceContext			*_deviceCtx{};

	/** Is current render context valid? */
	bool										_isValid{};

	/** Recreate the d3d11 context. */
	void recreateContext( );
	/** Destroy the d3d11 context. */
	void destroyContext( );

public:
	inline constexpr RenderSystem( ) = default;

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

inline auto gRender = std::make_unique< RenderSystem >( );