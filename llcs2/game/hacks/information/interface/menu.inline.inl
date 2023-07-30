#pragma once

inline bool hacks::Menu::onStateChange( ) {
	return _state = !_state;
}

inline bool hacks::Menu::getState( ) {
	return _state;
}