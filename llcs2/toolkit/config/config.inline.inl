#pragma once

inline bool Config::isPathValid( const std::filesystem::path &path ) {
	const auto status = std::filesystem::status( path );

	const auto readable = std::filesystem::_Bitmask_includes(
		status.permissions( ), std::filesystem::perms::group_read
	);

	const auto exists = status.type( ) != std::filesystem::file_type::none;

	const auto valid = hash( path.extension( ).c_str( ) ) == _( kConfigExtension );

	return exists && readable && valid;
}

template < typename _Type >
	requires detail::kIsConfigValue< _Type >
inline _Type *Config::getValueForWrite( const std::size_t name ) {
	return reinterpret_cast<_Type *>( &_elements[ name ]._bytes );
}

template < typename _Type >
	requires detail::kIsConfigValue< _Type >
inline _Type Config::getValue( const std::size_t name ) {
	return *reinterpret_cast<_Type *>( &_elements[ name ]._bytes );
}

template < typename _Type >
	requires detail::kIsConfigValue< _Type >
inline _Type Config::setValue( const std::size_t name, const _Type &value ) {
	//if constexpr ( sizeof( _Type ) > 16u )
	//	return _Type{};

	using Bytes = std::array< std::uint8_t, sizeof( _Type ) >;

	for ( std::size_t i{}; i < sizeof( _Type ); i++ )
		_elements[ name ]._bytes.at( i ) = reinterpret_cast< const Bytes * >( &value )->at( i );

	return value;
}

inline std::wstring_view Config::getName( ) const {
	return _path.filename( ).c_str( );
}

inline void Config::setName( const std::wstring_view to ) {
	const auto old_path = _path;

	_path.replace_filename( to );

	std::filesystem::rename( old_path, _path );
}

inline bool Config::isEmpty( ) const {
	return _elements.empty( );
}

inline void Config::clear( ) {
	_elements.clear( );
}