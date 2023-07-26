#include <game/game.hpp>

BoundingBox EspSystem::buildBoundingBox( valve::BaseEntity *entity ) const {
	if ( !entity )
		return {};

	auto collision = entity->getCollisionProperty( );
	if ( !collision )
		return {};

	auto node = entity->getSceneNode( );
	if ( !node )
		return {};

	BoundingBox res{};

	const auto maxs = collision->getMaxs( );

	glm::vec2 head{}, feet{};

	if ( !_renderSystem->projectViewToScreen( node->getAbsOrigin( ) + glm::vec3{ 0.f, 0.f, maxs.z }, head ) )
		return {};

	if ( !_renderSystem->projectViewToScreen( node->getAbsOrigin( ), feet ) )
		return {};

	const auto center = ( feet.x + head.x ) * 0.5f,
		width = maxs.x * ( feet.y - head.y ) / maxs.z;

	res.w = feet.y;
	res.z = head.y;
	res.x = center - width;
	res.y = center + width;

	return res;
}

void EspSystem::pushName( const EntityContext &ctx ) const {
	const auto &info = ctx._nameDrawInfo;
	if ( !info._draw )
		return;

	_renderSystem->getFont( _( "calibri16" ) ).drawText(
		info._text, info._position, Font::kLeft, { 1.f, 1.f, 1.f, 1.f }
	);
}

void EspSystem::pushHealth( const EntityContext &ctx ) const {
	const auto &info = ctx._healthDrawInfo;
	if ( !info._draw )
		return;

	_renderSystem->pushRectangle( info._boundingBox.getOrigin( ),
		info._boundingBox.getExtent( ), { 0.f, 0.f, 0.f, 1.f }, true, true
	);

	const auto new_height = info._boundingBox.getExtent( ).y
		* ctx._targetEntity->getHealth( ) * .01f;

	const glm::vec2 new_extent{
		-info._boundingBox.getExtent( ).x,
		-new_height
	};

	_renderSystem->pushRectangle( info._boundingBox.getBottomRight( ),
		new_extent, info._color, false, true
	);
}

void EspSystem::pushBox( const EntityContext &ctx ) const {
	const auto &info = ctx._boxDrawInfo;
	if ( !info._draw )
		return;

	_renderSystem->pushRectangle( info._boundingBox.getOrigin( ),
		info._boundingBox.getExtent( ), info._color
	);
	
	_renderSystem->pushRectangle( info._boundingBox.getOrigin( ),
		info._boundingBox.getExtent( ), info._color
	);
}

/** Should we pull the text coordinates and shit at this stage or during the fsn phase?
	 Additional W2S computation may result in a slight performance decrease during the rendering
	 phase. So we can just do it in the game thread while we're waiting for the render thread to
	 present the frame. */
void EspSystem::onPresent( ) {
	if ( !_active
		|| !valve::_engine->isInGame( ) )
		return;

	_contextList.clear( );

	valve::_entitySystem->forEachIdentity(
		std::bind( &EspSystem::storeContext, this, std::placeholders::_1 )
	);

	for ( const auto &ctx : _contextList ) {
		pushName( ctx );
	 	pushHealth( ctx );
		pushBox( ctx );
	}
}