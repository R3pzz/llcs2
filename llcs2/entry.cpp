#include "share/share.hpp"

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID res ) {
	if ( reason != DLL_PROCESS_ATTACH )
		return FALSE;

	std::thread{ [ ]( ) { runtime->init( ); } }.detach( );

	return TRUE;
}