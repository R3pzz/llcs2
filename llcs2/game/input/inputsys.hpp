#pragma once

#include "hotkeysys.hpp"

class InputSystem {
	_LLCS2_NO_COPY( InputSystem );

	friend LRESULT WINAPI CustomWindowProc( HWND wnd, UINT msg,
		WPARAM wparam, LPARAM lpraram
	);

	/** The game's original window process */
	WNDPROC				_originalWindowProc{};
	/** The game's main window */
	HWND					_mainWindow{};

	/** The hotkey system */
	HotkeySystem	_hotkeySystem{};

	/** Polls the hotkeys and other callbacks */
	void onPoll( UINT msg, WPARAM wparam, LPARAM lparam );

public:
	inline constexpr InputSystem( ) = default;

	/** Initializes input hooks and the hotkey system */
	void initializeAll( );

	/** Removes all of the hooks and deinitializes the hotkey system */
	void shutdownAll( );

	/** Getter for the hotkey system */
	inline HotkeySystem &getHotkeySystem( );
};

inline const auto gInput = std::make_unique< InputSystem >( );

#include "inputsys.inline.inl"