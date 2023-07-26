#pragma once

inline void ConfigSystem::getAllConfigsInDir( ConfigMap &out ) const {
	for ( auto &config : std::filesystem::directory_iterator{ _workingPath } ) {
		const auto filename = hash( config.path( ).extension( ).c_str( ) );

		if ( filename != _( Config::kConfigExtension ) )
			continue;
		
		if ( out.find( filename ) != out.end( ) )
			continue;

		out.insert_or_assign( filename, new Config{ config.path( ) } );
	}
}

inline Config *ConfigSystem::getActive( ) {
	return _currentConfig;
}

inline bool ConfigSystem::loadConfig( const std::wstring_view name ) {
	if ( name.empty( ) )
		return false;

	
}

inline bool ConfigSystem::saveConfig( const std::wstring_view name ) {
	/** This may throw an exception. If happens, there
			definitely is a bug in the config interface api... */
	auto recipient = name.empty( )
		? _currentConfig
		: _configs.at( hash( name.data( ) ) );

	if ( !recipient )
		_LLCS2_LOG_IMPORTANT( "[Config System] | saveConfig | There is no active config!!!\n" );
	else
		return recipient->saveToFile( );
}

inline bool ConfigSystem::deleteConfig( const std::wstring_view name ) {
	auto recipient = name.empty( )
		? _currentConfig
		: _configs.at( hash( name.data( ) ) );

	if ( !recipient )
		_LLCS2_LOG_IMPORTANT( "[Config System] | saveConfig | There is no active config!!!\n" );
	
	
}