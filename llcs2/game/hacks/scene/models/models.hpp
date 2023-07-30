#pragma once

namespace hacks {
	class Models {
		_LLCS2_NO_COPY( Models );

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
		inline constexpr Models( ) = default;

		void onFrameStageNotify( const valve::FrameStage stage );

		valve::Material *onGetMaterialForDraw( valve::SceneObjectDesc *obj, valve::Material *mat,
			valve::MaterialDrawDesc *desc, valve::SceneLayer *layer, bool *is_shadow
		);
	};

	inline auto _models = std::make_unique< Models >( );
}

#include "models.inline.inl"