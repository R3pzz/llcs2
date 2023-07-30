#include <game/game.hpp>

HRESULT __stdcall hooks::present( IDXGISwapChain *swapchain,
	const std::uint32_t sync, const std::uint32_t flags
) {
	_renderSystem->onPresentPre( swapchain, sync, flags );

	hacks::_menu->onPresent( );

	hacks::_esp->onPresent( );

	_renderSystem->onPresentPost( swapchain, sync, flags );

	return _originalPresent( swapchain, sync, flags );
}

HRESULT __stdcall hooks::resizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
	const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
) {
	_renderSystem->onResizeBuffers( swapchain, buf_count, width, height, new_format, flags );

	return _originalResizeBuffers( swapchain, buf_count, width, height, new_format, flags );
}

void __fastcall hooks::frameStageNotify( const Mem client,
	const valve::FrameStage stage
) {
	hacks::_shading->onFrameStageNotify( stage );

	return _originalFrameStageNotify( client, stage );
}

valve::Material *__fastcall hooks::getMaterialForDraw( valve::SceneObjectDesc *obj, valve::Material *mat,
	valve::MaterialDrawDesc *desc, valve::SceneLayer *layer, bool *is_shadow
) {
	return hacks::_models->onGetMaterialForDraw( obj, mat, desc, layer, is_shadow );
}