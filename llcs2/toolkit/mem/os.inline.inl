#pragma once

inline auto os::uni_string_t::wstr( ) const {
	return std::wstring{ m_data, m_length / sizeof( wchar_t ) };
}

inline void os::ldr_data_t::for_each_in_load_entry( const std::function< bool( ldr_entry_t * ) > &fn ) {
	for ( auto record = &m_in_load_modules; record != m_in_load_modules.Blink; record = record->Flink ) {
		auto entry = CONTAINING_RECORD( record, ldr_entry_t, m_in_load_links );
		if ( !entry )
			continue;

		if ( fn( entry ) )
			return;
	}
}

inline auto os::peb( ) {
	return reinterpret_cast< peb_t * >( __readgsqword( 0x60ul ) );
}

inline auto pe_desc_t::dos_hdr( ) const {
	return m_base.as< PIMAGE_DOS_HEADER >( );
}

inline auto pe_desc_t::nt_hdr( ) const {
	return m_base.offset( dos_hdr( )->e_lfanew ).as< PIMAGE_NT_HEADERS64 >( );
}

inline auto pe_desc_t::size( ) const {
	return nt_hdr( )->OptionalHeader.SizeOfImage;
}

inline auto pe_desc_t::start( ) const {
	return m_base;
}

inline auto pe_desc_t::end( ) const {
	return m_base.offset( size( ) );
}