#pragma once

/** Under construction... */
class ConfigSystem {
	_LLCS2_NO_COPY( ConfigSystem );

	typedef
		std::unordered_map< std::size_t,
			Config *
		>
		ConfigMap;

	std::filesystem::path _workingPath{};
	ConfigMap							_configs{};
	Config								*_currentConfig{};

	inline void getAllConfigsInDir( ConfigMap &out ) const;

public:
	inline constexpr ConfigSystem( ) = default;

	inline Config *getActive( );

	inline bool loadConfig( const std::wstring_view name );

	inline bool saveConfig( const std::wstring_view name );

	inline bool deleteConfig( const std::wstring_view name );

	void initializeAll( );
};

/** Under construction... */
//inline auto _configSystem = std::make_unique< ConfigSystem >( );

#include "configsys.inline.inl"