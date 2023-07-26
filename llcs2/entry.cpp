#include <game/game.hpp>

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID res ) {
	if ( reason != DLL_PROCESS_ATTACH )
		return FALSE;

	std::thread{ [ ]( ) { _runtime->initializeWorkers( ); } }.detach( );

	return TRUE;
}