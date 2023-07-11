#include <game/game.hpp>

bool on_exit( ) {
	std::exit( 0 );

	return true;
}

bool on_print( ) {
	_LLCS2_LOG( "on_print has been called\n" );

	/* this hotkey should never be on */
	return false;
}

bool on_local_player( ) {
	const auto local = valve::gEntitySystem->getEntity( 1u );

	_LLCS2_LOG_IMPORTANT( "[Main Thread] | Found local player at %p\n", local );

	return false;
}

void HotkeySystem::onPoll( UINT msg, WPARAM wparam, LPARAM lparam ) {
	if ( !_enabled )
		return;

	if ( msg != WM_KEYDOWN
		&& msg != WM_SYSKEYDOWN
		&& msg != WM_KEYUP
		&& msg != WM_SYSKEYUP )
		return;

	const auto is_down = msg == WM_KEYDOWN
										|| msg == WM_SYSKEYDOWN;

	for ( auto pair : _hotkeyTable ) {
		if ( pair.first != wparam )
			continue;

		for ( auto desc : pair.second ) {
			if ( !desc._system )
				if ( !desc._enabled )
					continue;

			Bitfield< std::uint64_t > flags = lparam;

			const auto was_active = flags.at( 30ull );
			const auto press_times = static_cast< std::uint8_t >( lparam );

			switch ( desc._activation ) {
			case HotkeyDesc::kToggle: {
				if ( !is_down )
					continue;

				if ( was_active )
					continue;

				desc._active = desc._callback( );

				continue;
			}
			case HotkeyDesc::kHold: {
				if ( is_down )
					if ( !desc._active )
						desc._active = desc._callback( );
				else
					if ( desc._active )
						desc._active = desc._callback( );

				continue;
			}
			case HotkeyDesc::kInverseHold: {
				if ( is_down )
					if ( desc._active )
						desc._active = desc._callback( );
				else
					if ( !desc._active )
						desc._active = desc._callback( );

				continue;
			}
			case HotkeyDesc::kDoublePress: {
				if ( press_times == 2u )
					desc._active = desc._callback( );

				continue;
			}
			default:
				continue;
			}
		}
	}
}

void HotkeySystem::initializeSystemHotkeys( ) {
	addHotkey( VK_END,	{ true, true, HotkeyDesc::kToggle, on_exit	} );
	addHotkey( VK_HOME, { true, true, HotkeyDesc::kToggle, on_print } );
	addHotkey( VK_UP,		{ true, true, HotkeyDesc::kToggle, on_local_player } );
}

bool HotkeySystem::addHotkey( const std::size_t scan_code,
	const HotkeyDesc &desc, const bool skip_scan
) {
	/* If we can't add this hotkey, indicate that */
	if ( !skip_scan )
		if ( !checkForInsert( scan_code, desc ) )
			return false;

	const auto it = _hotkeyTable.find( scan_code );

	/* If there was no such a scan code in the table, insert it and add the desc */
	if ( it == _hotkeyTable.end( ) ) {
		auto descs = _hotkeyTable.insert_or_assign( scan_code, HotkeyDescs{} ).first;

		descs->second.push_back( desc );
	}
	/* Otherwise, just push the desc */
	else {
		it->second.push_back( desc );
	}

	return true;
}

bool HotkeySystem::removeHotkey( const std::size_t scan_code,
	const Mem func
) {
	const auto descs = _hotkeyTable.find( scan_code );
	if ( descs == _hotkeyTable.end( ) )
		return false;

	if ( !func._base ) {
		descs->second.clear( );

		return true;
	}

	for ( auto it = descs->second.begin( ); it != descs->second.end( ); it++ ) {
		if ( it->_callback == func.as< HotkeyDesc::CallbackFn >( ) ) {
			descs->second.erase( it );

			return true;
		}
	}

	return false;
}