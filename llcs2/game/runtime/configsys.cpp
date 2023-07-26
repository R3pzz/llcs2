#include <game/game.hpp>

void ConfigSystem::initializeAll( ) {
	PWSTR documents{};

	SHGetKnownFolderPath( FOLDERID_Documents, 0u, {}, &documents );
	if ( !documents ) {
		_LLCS2_LOG_IMPORTANT( "[Main Thread] | Config system initialization failed, cannot find the documents folder\n" );

		return;
	}

	_workingPath.append( documents ).append( "llcs2" );

	if ( !std::filesystem::exists( _workingPath ) ) {
		if ( !std::filesystem::create_directories( _workingPath ) )
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Config system initialization failed, cannot create the configs folder\n" );
		else
			_LLCS2_LOG_IMPORTANT( "[Main Thread] | Config system initialization successful\n" );
	}
}