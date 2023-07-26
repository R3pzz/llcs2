#pragma once

inline bool EspSystem::storeContext( valve::EntityIdentity *identity ) {
	auto ent = identity->getOwner< valve::CSPlayerPawn >( );
	if ( !ent
		|| !ent->isPlayerPawn( ) )
		return false;

	auto node = ent->getSceneNode( );
	if ( !node )
		return false;

	auto collision = ent->getCollisionProperty( );
	if ( !collision )
		return false;

	/** This is bad tho. Gotta add this method to Handle struct itself... */
	auto controller = valve::_entitySystem->getEntity(
		ent->getController( )
	)->as< valve::CSPlayerController >( );

	EntityContext ctx{ ent };

	const auto bbox = buildBoundingBox( ent );

	if ( ent->isPlayerPawn( ) ) {
		if ( !controller || !bbox.isValid( ) )
			return false;

		{
			ctx._nameDrawInfo._draw = true;
			ctx._nameDrawInfo._position = bbox.getTopRight( ) + glm::vec2{ 4.f, 0.f };
			ctx._nameDrawInfo._text = std::string{ controller->getPlayerName( ), 128u };
		}

		{
			ctx._boxDrawInfo._draw = true;
			ctx._boxDrawInfo._boundingBox = bbox;
		}

		{
			const auto x_offset = ctx._healthDrawInfo._thickness + 6.f;

			ctx._healthDrawInfo._draw = true;
			ctx._healthDrawInfo._color = ent->healthAsColor( );

			ctx._healthDrawInfo._boundingBox = {
				{ bbox.x - x_offset, bbox.x - 4.f },
				{ bbox.z, bbox.w }
			};
		}
	}

	_contextList.push_back( std::move( ctx ) );

	return false;
}

inline void EspSystem::setState( const bool to ) {
	_active = to;
}

inline bool EspSystem::getState( ) const {
	return _active;
}