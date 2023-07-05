#pragma once

#include <game/input/inputsys.hpp>

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
			std::size_t, Mem
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

	/** The console's out stream */
	std::FILE				*_consoleOut{};

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

public:
	inline constexpr Runtime( ) = default;

	void initializeWorkers( );
};

inline const auto gRuntime = std::make_unique< Runtime >( );