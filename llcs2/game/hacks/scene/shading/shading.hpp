#pragma once

namespace hacks {
	class Shading {
		_LLCS2_NO_COPY( Shading );

		/** Saved data */
		float _oldExpMin{}, _oldExpMax{};

	public:
		inline constexpr Shading( ) = default;

		void onFrameStageNotify( const valve::FrameStage stage );
	};

	inline auto _shading = std::make_unique< Shading >( );
}