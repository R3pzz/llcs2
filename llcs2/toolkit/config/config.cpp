#include <toolkit/toolkit.hpp>

Config *Config::loadFromFile( const std::filesystem::path &path ) {
	if ( !isPathValid( path ) )
		return nullptr;

	auto cfg = new Config{};
	if ( !cfg )
		return nullptr;

	auto stream = std::ifstream{ path };
	if ( !stream.is_open( ) )
		return nullptr;

	const auto obj = nlohmann::json::parse( stream );

	stream.close( );

	if ( obj.empty( ) )
		return nullptr;

	for ( auto &node : obj ) {
		if ( !obj.is_object( ) )
			continue;

		const auto hash = node[ "hash" ].get< std::size_t >( );
		if ( !hash )
			continue;

		const auto value = node[ "value" ].get< typename Element::SerializedBytes >( );

		cfg->_elements.insert_or_assign( hash, Element{ hash, value } );
	}

	cfg->_path = path;

	return cfg;
}

bool Config::saveToFile( ) {
	if ( !isPathValid( _path ) )
		return false;
	
	nlohmann::json obj{};

	for ( const auto &element : _elements ) {
		obj[ std::to_string( element.second._hash ) ] = {
			{ "hash", element.first }, { "value", element.second._bytes }
		};
	}

	auto stream = std::ofstream{ _path };
	if ( !stream.is_open( ) )
		return false;

	stream << obj;

	stream.close( );

	return true;
}

bool Config::deleteFile( ) {
	if ( !isPathValid( _path ) )
		return false;

	return std::filesystem::remove( _path );
}