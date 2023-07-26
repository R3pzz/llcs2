#pragma once

namespace hooks {
	HRESULT __stdcall present( IDXGISwapChain *swapchain,
		const std::uint32_t sync, const std::uint32_t flags
	);

	inline decltype( &present ) _originalPresent{};

	HRESULT __stdcall resizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
		const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
	);

	inline decltype( &resizeBuffers ) _originalResizeBuffers{};

	void __fastcall frameStageNotify( const Mem client,
		const valve::FrameStage stage
	);

	inline decltype( &frameStageNotify ) _originalFrameStageNotify{};

	valve::Material *__fastcall getMaterialForDraw( valve::SceneObjectDesc *obj, valve::Material *mat,
		valve::MaterialDrawDesc *desc, valve::SceneLayer *layer, bool *is_shadow
	);

	inline decltype( &getMaterialForDraw ) _originalGetMaterialForDraw{};
}