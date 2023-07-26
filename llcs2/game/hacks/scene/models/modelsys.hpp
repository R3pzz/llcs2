#pragma once

class ModelSystem {
	_LLCS2_NO_COPY( ModelSystem );

	struct ModelRenderInfo {
		struct {

		} _glowInfo{};

		struct {

		} _materialInfo{};
	};

	typedef
		std::vector< ModelRenderInfo >
		InfoTable;

	InfoTable _renderInfos{};

	struct {

	} _lightingInfo{};

	inline void applyGlowEffect( const ModelRenderInfo &info );

	inline void applyLighting( );

	inline bool dispatchEntity( valve::EntityIdentity *identity );

public:
	inline constexpr ModelSystem( ) = default;

	void onFrameStageNotify( const valve::FrameStage stage );

	valve::Material *onGetMaterialForDraw( valve::SceneObjectDesc *obj, valve::Material *mat,
		valve::MaterialDrawDesc *desc, valve::SceneLayer *layer, bool *is_shadow
	);
};

inline auto _modelSystem = std::make_unique< ModelSystem >( );

#include "modelsys.inline.inl"