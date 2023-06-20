#include <toolkit/toolkit.hpp>

void dump_interfaces( const pe_desc_t pe ) {
	struct inode_t {
		using fn_getter_t = ptr_t( __cdecl * )( );

		inline constexpr inode_t( ) = default;

		fn_getter_t			m_getter{};
		const char			*m_name{};
		inode_t					*m_next{};
	};

	const auto base = GetProcAddress( pe.m_base.as< HMODULE >( ), "CreateInterface" );
	if ( !base )
		return;

	auto entry = *ptr_t{ base }.jump( 0x3ll ).offset( 0x7ll ).as< inode_t ** >( );

	std::wprintf( L"[InterfaceWalk] | Interface list start at %p\n", entry );

	for ( auto i = entry; i; i = i->m_next )
		std::printf( "[InterfaceWalk] | Interface found: %s (addr: %p)\n", i->m_name, i->m_getter( ).m_base );
}

void worker( ) {
	std::FILE *confile{};

	AllocConsole( );
	AttachConsole( ATTACH_PARENT_PROCESS );

	freopen_s( &confile, "CONOUT$", "w", stdout );

	const auto peb = os::peb( );
	const auto ldr = peb->m_ldr_data;

	auto ldr_entry_subroutine = [ ]( os::ldr_entry_t *entry ) {
		if ( entry->m_base_dll_name.wstr( ).find( L"inputsystem" ) == std::wstring::npos )
			return false;

		dump_interfaces( entry->m_dll_base );

		return true;
	};

	ldr->for_each_in_load_entry( ldr_entry_subroutine );

	while ( true )
		std::this_thread::sleep_for( std::chrono::seconds{ 20u } );

	std::fclose( confile );

	FreeConsole( );
}

BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID res ) {
	if ( reason != DLL_PROCESS_ATTACH )
		return FALSE;

	std::thread{ [ ]( ) { worker( ); } }.detach( );

	return TRUE;
}