#pragma once

inline auto os::UniString::wstr( ) const {
	return std::wstring{ _data, _length / sizeof( wchar_t ) };
}

inline void os::LdrData::forEachInLoadEntry(
	const std::function< bool( LdrEntry * ) > &fn
) {
	for ( auto record = &_inLoadModules; record != _inLoadModules.Blink; record = record->Flink ) {
		auto entry = CONTAINING_RECORD( record, LdrEntry, _inLoadLinks );
		if ( !entry )
			continue;

		if ( fn( entry ) )
			return;
	}
}

inline auto os::peb( ) {
	return reinterpret_cast< Peb * >( __readgsqword( 0x60ul ) );
}

inline auto PeDesc::dosHeader( ) const {
	return _base.as< PIMAGE_DOS_HEADER >( );
}

inline auto PeDesc::ntHeader( ) const {
	return _base.offset( dosHeader( )->e_lfanew ).as< PIMAGE_NT_HEADERS64 >( );
}

inline auto PeDesc::size( ) const {
	return ntHeader( )->OptionalHeader.SizeOfImage;
}

inline auto PeDesc::start( ) const {
	return _base;
}

inline auto PeDesc::end( ) const {
	return _base.offset( size( ) );
}