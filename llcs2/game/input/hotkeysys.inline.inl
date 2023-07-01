#pragma once

inline constexpr bool HotkeyDesc::equals( const HotkeyDesc &other ) const {
	return _callback == other._callback ? true : false;
}

inline bool HotkeySystem::checkForInsert( const std::size_t scan_code,
	const HotkeyDesc &desc
) const {
	/* Check if we already have the same scan code registered */
	const auto it = _hotkeyTable.find( scan_code );
	if ( it == _hotkeyTable.end( ) )
		return true;

	/* If yes, then ensure we're trying to add a different hotkey */
	const auto &descs = _hotkeyTable.at( scan_code );

	for ( std::size_t i{}; i < descs.size( ); i++ )
		if ( descs.at( i ).equals( desc ) )
			return false;

	return true;
}

inline bool HotkeySystem::getState( ) const {
	return _enabled;
}

inline void HotkeySystem::setState( const bool to ) {
	_enabled = to;
}