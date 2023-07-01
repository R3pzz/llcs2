#include <game/runtime/runtime.hpp>

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID res ) {
	if ( reason != DLL_PROCESS_ATTACH )
		return FALSE;

	std::thread{ [ ]( ) { gRuntime->initializeWorkers( ); } }.detach( );

	return TRUE;
}