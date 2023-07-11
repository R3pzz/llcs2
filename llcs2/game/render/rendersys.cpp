#include <game/game.hpp>

void RenderSystem::recreateContext( ) {
	ID3D11Texture2D *buffer{};

	_swapchain->GetBuffer( 0u, IID_PPV_ARGS( &buffer ) );
	if ( !buffer )
		return;

	_swapchain->GetDevice( IID_PPV_ARGS( &_device ) );
	if ( !_device )
		return;

	_device->CreateRenderTargetView( buffer, nullptr, &_renderTarget );
	if ( !_renderTarget )
		return;

	_device->GetImmediateContext( &_deviceCtx );
	if ( !_deviceCtx )
		return;

	ImGui_ImplDX11_Init( _device, _deviceCtx );

	_isValid = true;
}

void RenderSystem::destroyContext( ) {
	_isValid = false;

	if ( _renderTarget ) {
		_renderTarget->Release( );

		_renderTarget = nullptr;
	}

	if ( _deviceCtx ) {
		_deviceCtx->Release( );

		_deviceCtx = nullptr;
	}

	if ( _device ) {
		_device->Release( );

		_device = nullptr;
	}

	ImGui_ImplDX11_Shutdown( );
}

void RenderSystem::initializeAll( ) {
	_swapchain = valve::gRenderDeviceDx11->getSwapchain( )->_swapchain; 
	if ( !_swapchain )
		return;

	ID3D11Texture2D *buffer{};

	_swapchain->GetBuffer( 0u, IID_PPV_ARGS( &buffer ) );
	if ( !buffer )
		return;

	_LLCS2_LOG_IMPORTANT( "[Render] | Got the swapchain buffer\n" );

	_swapchain->GetDevice( IID_PPV_ARGS( &_device ) );
	if ( !_device )
		return;

	_device->CreateRenderTargetView( buffer, nullptr, &_renderTarget );
	if ( !_renderTarget )
		return;

	_device->GetImmediateContext( &_deviceCtx );
	if ( !_deviceCtx )
		return;

	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( gInput->getPlatformWindow( ) );
	ImGui_ImplDX11_Init( _device, _deviceCtx );

	_isValid = true;

	_LLCS2_LOG_IMPORTANT( "[Render] | Initialization successful\n" );
}

void RenderSystem::onPresentPre( IDXGISwapChain *swapchain,
	const std::uint32_t sync, const std::uint32_t flags
) {
	if ( !_isValid )
		recreateContext( );

	ImGui_ImplDX11_NewFrame( );
	ImGui_ImplWin32_NewFrame( );

	ImGui::NewFrame( );
}

void RenderSystem::onPresentPost( IDXGISwapChain *swapchain,
	const std::uint32_t sync, const std::uint32_t flags
) {
	ImGui::Render( );

	_deviceCtx->OMSetRenderTargets( 1u, &_renderTarget, nullptr );
	
	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
}

void RenderSystem::onResizeBuffers( IDXGISwapChain *swapchain, const std::uint32_t buf_count,
	const std::uint32_t width, const std::uint32_t height, const DXGI_FORMAT new_format, const std::uint32_t flags
) {
	destroyContext( );

	_LLCS2_LOG_IMPORTANT( "[Render Thread] | onResizeBuffers called!\n" );
}