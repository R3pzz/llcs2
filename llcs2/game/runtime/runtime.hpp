#pragma once

class Runtime {
	_LLCS2_NO_COPY( Runtime );

	typedef
		std::unordered_map<
			std::size_t, PeDesc
		>
		ModulesTable;

	typedef
		std::unordered_map<
			std::size_t, Mem
		>
		InterfaceTable;

	typedef
		std::unordered_map<
			std::size_t, Mem
		>
		AuxAddressTable;

	typedef
		std::unordered_map<
			std::size_t, std::ptrdiff_t
		>
		OffsetTable;

	/** A list of the modules we've managed to parse from PEB */
	ModulesTable		_knownModules{};
	/** A list of the interfaces we've managed to parse extract from the game's modules */
	InterfaceTable	_knownInterfaces{};
	/** A list of the addresses we've managed to find/pattern-scan */
	AuxAddressTable _auxAddresses{};
	/* A list of the offsets we've managed to extract from the schema system */
	OffsetTable			_knownOffsets{};

	/** Logging streams */
	std::FILE				*_consoleOut{}, *_logOut{};

	/** The default cheat config */
	Config					*_defaultConfig{};

	/** Attaches a console to the parent process */
	void attachConsole( );
	/** Detaches the console from the game process */
	void detachConsole( );
	/** Parses the PEB for modules */
	void extractModuleData( );
	/** Parses the modules for the byte patterns */
	void findAuxAddresses( );
	/** Initializes the input system */
	void initializeInput( );
	/** Initializes the render system */
	void initializeRender( );
	/** Caches the default cheat config */
	void cacheDefaultConfig( );
	/** Initializes the hooks */
	void initializeHooks( );

public:
	inline constexpr Runtime( ) = default;

	inline std::ptrdiff_t getOffset( const std::size_t name ) const;

	inline PeDesc getPeDesc( const std::size_t name ) const;

	inline std::FILE *getLogOut( );

	inline Config *getConfig( );

	void initializeWorkers( );
};

inline const auto _runtime = std::make_unique< Runtime >( );

#include "runtime.inline.inl"