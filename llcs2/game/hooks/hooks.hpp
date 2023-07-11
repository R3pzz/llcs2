#pragma once

namespace hooks {
	HRESULT __stdcall present( IDXGISwapChain *swapchain,
		const std::uint32_t sync, const std::uint32_t flags
	);

	inline decltype( &present ) gOriginalPresent{};

	HRESULT __stdcall resizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
		const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
	);

	inline decltype( &resizeBuffers ) gOriginalResizeBuffers{};
}