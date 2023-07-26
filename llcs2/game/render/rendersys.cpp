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

bool RenderSystem::projectViewToScreen( const glm::vec3 &view, glm::vec2 &screen ) {
	if ( !_swapchain
		|| !valve::_mvpMatrix )
		return false;

	DXGI_SWAP_CHAIN_DESC desc{};

	_swapchain->GetDesc( &desc );

	const int width = desc.BufferDesc.Width,
		height = desc.BufferDesc.Height;

	const auto &mat = *valve::_mvpMatrix;

	const auto clip_coords = glm::vec4{
		mat[ 0u ][ 0u ] * view[ 0u ] + mat[ 0u ][ 1u ] * view[ 1u ] + mat[ 0u ][ 2u ] * view[ 2u ] + mat[ 0u ][ 3u ],
		mat[ 1u ][ 0u ] * view[ 0u ] + mat[ 1u ][ 1u ] * view[ 1u ] + mat[ 1u ][ 2u ] * view[ 2u ] + mat[ 1u ][ 3u ],
		0.f,
		mat[ 3u ][ 0u ] * view[ 0u ] + mat[ 3u ][ 1u ] * view[ 1u ] + mat[ 3u ][ 2u ] * view[ 2u ] + mat[ 3u ][ 3u ]
	};

	/** No need to calculate the off-depth vector here i guess */
	if ( clip_coords.w < .001f )
		return false;

	glm::vec2 nd_coords{};

	nd_coords.x = clip_coords.x / clip_coords.w;
	nd_coords.y = clip_coords.y / clip_coords.w;

	screen.x = nd_coords.x * width * .5f + width * .5f;
	screen.y = nd_coords.y * -height * .5f + height * .5f;

	return true;
}

void RenderSystem::initializeAll( ) {
	_swapchain = valve::_renderDevice->getSwapchain( )->_swapchain; 
	if ( !_swapchain )
		return;

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

	ImGui::CreateContext( );

	{
		Font calibri16{};

		if ( !calibri16.fromTtf( "C:\\Windows\\Fonts\\calibri.ttf", Font::kOutlined, 16.f ) )
			_LLCS2_LOG_IMPORTANT( "[Render] | Failed to initialize calibri16 font\n" );

		_fontTable.insert_or_assign( _( "calibri16" ), std::move( calibri16 ) );
	}

	ImGui_ImplWin32_Init( _inputSystem->getPlatformWindow( ) );
	ImGui_ImplDX11_Init( _device, _deviceCtx );

	_isValid = true;
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

	_swapchain = valve::_renderDevice->getSwapchain( )->_swapchain;

	_LLCS2_LOG_IMPORTANT( "[Render Thread] | onResizeBuffers called!\n" );
}