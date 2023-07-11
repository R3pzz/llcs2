#include <game/game.hpp>

HRESULT __stdcall hooks::present( IDXGISwapChain *swapchain,
	const std::uint32_t sync, const std::uint32_t flags
) {
	gRender->onPresentPre( swapchain, sync, flags );

	ImGui::GetForegroundDrawList( )->AddRectFilled( { 0.f, 0.f }, { 100.f, 100.f },
		ImGui::ColorConvertFloat4ToU32( { 1.f, .5f, 1.f, 1.f } )
	);

	gRender->onPresentPost( swapchain, sync, flags );

	return gOriginalPresent( swapchain, sync, flags );
}

HRESULT __stdcall hooks::resizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
	const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
) {
	gRender->onResizeBuffers( swapchain, buf_count, width, height, new_format, flags );

	return gOriginalResizeBuffers( swapchain, buf_count, width, height, new_format, flags );
}