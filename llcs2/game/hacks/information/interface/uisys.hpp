#pragma once

class UiSystem {
	_LLCS2_NO_COPY( UiSystem );

public:
	inline constexpr UiSystem( ) = default;

	void onPresent( );
};

inline auto _uiSystem = std::make_unique< UiSystem >( );

#include "uisys.inline.inl"