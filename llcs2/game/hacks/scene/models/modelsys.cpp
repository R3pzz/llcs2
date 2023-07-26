#include <game/game.hpp>

void ModelSystem::onFrameStageNotify( const valve::FrameStage stage ) {
	if ( stage != valve::FrameStage::kRenderStart )
		return;

	valve::_entitySystem->forEachIdentity(
		std::bind( &ModelSystem::dispatchEntity, this, std::placeholders::_1 )
	);

	for ( const auto &info : _renderInfos ) {
		applyGlowEffect( info );
	}

	applyLighting( );
}

valve::Material *ModelSystem::onGetMaterialForDraw( valve::SceneObjectDesc *obj, valve::Material *mat,
	valve::MaterialDrawDesc *desc, valve::SceneLayer *layer, bool *is_shadow
) {
	if ( std::strstr( mat->getName( ), "characters/models" ) ) {
		valve::Material **new_mat{};

		valve::_materialSystem->findOrCreate( "materials/dev/reflectivity_90.vmat", &new_mat );

		if ( new_mat )
			return *new_mat;
	}

	return hooks::_originalGetMaterialForDraw( obj, mat, desc, layer, is_shadow );
}