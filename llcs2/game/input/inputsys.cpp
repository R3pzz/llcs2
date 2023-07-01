#include <game/runtime/runtime.hpp>

LRESULT WINAPI CustomWindowProc( HWND wnd, UINT msg,
	WPARAM wparam, LPARAM lparam
) {
	gInput->onPoll( msg, wparam, lparam );

	return CallWindowProcA( gInput->_originalWindowProc, wnd, msg, wparam, lparam );
}

void InputSystem::initializeAll( ) {
	_mainWindow = valve::gInputSystem->_windowHandles[ 0u ];
	if ( !_mainWindow )
		return;

	_originalWindowProc = reinterpret_cast< WNDPROC >(
		SetWindowLongPtrA( _mainWindow, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( CustomWindowProc ) )
	);

	_hotkeySystem.initializeSystemHotkeys( );

	_hotkeySystem.setState( true );
}

void InputSystem::shutdownAll( ) {
	_hotkeySystem.setState( false );

	SetWindowLongPtrA( _mainWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>( _originalWindowProc ) );
}

void InputSystem::onPoll( UINT msg, WPARAM wparam, LPARAM lparam ) {
	_hotkeySystem.onPoll( msg, wparam, lparam );
}