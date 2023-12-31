#include <game/game.hpp>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

LRESULT WINAPI CustomWindowProc( HWND wnd, UINT msg,
	WPARAM wparam, LPARAM lparam
) {
	_inputSystem->getHotkeySystem( ).setState( !hacks::_menu->getState( ) );
	_inputSystem->onPoll( msg, wparam, lparam );

	if ( ImGui_ImplWin32_WndProcHandler( wnd, msg, wparam, lparam ) )
		if ( hacks::_menu->getState( ) )
			return true;

	return CallWindowProcA( _inputSystem->_originalWindowProc, wnd, msg, wparam, lparam );
}

void InputSystem::initializeAll( ) {
	_mainWindow = valve::_inputSystem->_windowHandles[ 0u ];
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