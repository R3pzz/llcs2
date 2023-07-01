#pragma once

#include <toolkit/toolkit.hpp>

struct HotkeyDesc {
	typedef
		bool( __cdecl *
			CallbackFn
			)( );

	enum Activation : std::uint16_t {
		/** Activation by pressing the button */
		kToggle,
		/** Activation by holding the button */
		kHold,
		/** Dectivation by holding the button */
		kInverseHold,
		/** Activation by double-pressing the button */
		kDoublePress,
	};

		/** Does the hotkey recieve input */
	bool				_enabled{},
		/** Is this hotkey system-related */
							_system{};
	/** How is this hotkey activated */
	Activation	_activation{};
	/** Callback to be called on the corresponding key press */
	CallbackFn	_callback{};
	/** Is the hotkey currently active */
	bool				_active{};

	inline constexpr HotkeyDesc( ) = default;

	inline constexpr HotkeyDesc( const bool enabled, const bool system,
		const Activation activation, CallbackFn callback
	)
		: _enabled{ enabled },
			_system{ system },
			_activation{ activation },
			_callback{ callback }
	{}

	/** Is this hotkey same as the other one */
	inline constexpr bool equals( const HotkeyDesc &other ) const;
};

class HotkeySystem {
	_LLCS2_NO_COPY( HotkeySystem );

	friend class InputSystem;

	typedef
		std::vector< HotkeyDesc >
		HotkeyDescs;

	typedef
		std::unordered_map< std::size_t,
			HotkeyDescs
		>
		HotkeyTable;

	/** Table of hotkeys we're working in */
	HotkeyTable		_hotkeyTable{};
	/** Is the hotkey dispatch currently enabled */
	bool					_enabled{};

	void onPoll( UINT msg, WPARAM wparam, LPARAM lparam );

	/** A utility function to check if the same hotkey is already in the system */
	inline bool checkForInsert( const std::size_t scan_code,
		const HotkeyDesc &desc
	) const;

public:
	inline constexpr HotkeySystem( ) = default;

	/** Fill in the hotkey table with system hotkeys */
	void initializeSystemHotkeys( );

	/** Try to add a hotkey into the table. Can fail if one is a duplicate of another */
	bool addHotkey( const std::size_t scan_code,
		const HotkeyDesc &desc, const bool skip_scan = false
	);

	/** Try to remove a hotkey into the table. */
	bool removeHotkey( const std::size_t scan_code,
		const Mem func = nullptr
	);

	/** Are the hotkeys enabled */
	inline bool getState( ) const;

	/** Set the state of the hotkey system */
	inline void setState( const bool to );
};

#include "hotkeysys.inline.inl"