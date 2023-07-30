#pragma once

namespace hacks {
	class Menu {
		_LLCS2_NO_COPY( Menu );

		bool _state{};

	public:
		inline constexpr Menu( ) = default;

		inline bool onStateChange( );

		inline bool getState( );

		void onPresent( );
	};

	inline auto _menu = std::make_unique< Menu >( );
}

#include "menu.inline.inl"