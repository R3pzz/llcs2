#include <game/game.hpp>

void hacks::Shading::onFrameStageNotify( const valve::FrameStage stage ) {
	if ( stage != valve::FrameStage::kRenderStart )
		return;

	if ( !valve::_engine->isInGame( ) )
		return;

	if ( !_runtime->getConfig( )->getValue< bool >( _( "shading.enabled" ) ) )
		return;

	auto controller = valve::_entitySystem->getIdentity( 1u )->getOwner<
		valve::CSPlayerController
	>( );

	auto local = controller->getPawnHandle( ).resolve< valve::CSPlayerPawn >( );
	if ( !local )
		return;

	auto camera = local->getCameraServices( );
	if ( !camera )
		return;

	auto postprocess = camera->getPostProcessVolume( ).resolve< valve::PostProcessVolume >( );
	if ( !postprocess )
		return;
	
	auto &fog = camera->getCurrentFog( );

	if ( _runtime->getConfig( )->getValue< bool >( _( "shading.fog.enabled" ) ) ) {
		fog.getPrimColor( ) = _runtime->getConfig( )->getValue< glm::vec4 >( _( "shading.fog.primcolor" ) );
		fog.getSecColor( ) = _runtime->getConfig( )->getValue< glm::vec4 >( _( "shading.fog.seccolor" ) );
	
		fog.getStart( ) = _runtime->getConfig( )->getValue< float >( _( "shading.fog.start" ) );
		fog.getEnd( ) = _runtime->getConfig( )->getValue< float >( _( "shading.fog.end" ) );
	
		fog.getExponent( ) = _runtime->getConfig( )->getValue< float >( _( "shading.fog.exponent" ) );
		fog.getMaxDensity( ) = _runtime->getConfig( )->getValue< float >( _( "shading.fog.maxdensity" ) );

		fog.getDuration( ) = 9999999.f;
		fog.isEnabled( ) = true;
	}
	else {
		fog.isEnabled( ) = false;
	}

	if ( _runtime->getConfig( )->getValue< bool >( _( "shading.cc.enabled" ) ) ) {
		postprocess->getExpMin( ) = _runtime->getConfig( )->getValue< float >( _( "shading.cc.expmin" ) );
		postprocess->getExpMax( ) = _runtime->getConfig( )->getValue< float >( _( "shading.cc.expmax" ) );
	}
	else {
		postprocess->getExpMin( ) = 1.f;
		postprocess->getExpMax( ) = 1.f;
	}
}