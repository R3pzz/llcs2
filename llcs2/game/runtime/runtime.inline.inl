#pragma once

inline std::ptrdiff_t Runtime::getOffset( const std::size_t name ) const {
#ifdef _DEBUG
	const auto iter = _knownOffsets.find( name );
	if ( iter == _knownOffsets.end( ) ) {
		_LLCS2_LOG_IMPORTANT( "[Warning] | Failed to find the offset for a field hashed %zu\n", name );

		std::this_thread::sleep_for( std::chrono::seconds{ 10u } );

		return 0;
	}
#endif

	return _knownOffsets.at( name );
}

inline std::FILE *Runtime::getLogOut( ) {
	return _logOut;
}