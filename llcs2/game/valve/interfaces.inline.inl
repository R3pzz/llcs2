#pragma once

inline valve::BaseEntity *valve::EntitySystem::getEntity( const std::uint32_t idx ) {
	const auto chunk = *Mem{ this }.offset( 0x8 * ( idx >> 9u ) + 0x10 ).as< Mem * >( );
	if ( !chunk )
		return nullptr;

	return *chunk.offset( 0x78 * idx ).as< BaseEntity ** >( );
}

inline valve::BaseEntity *valve::EntitySystem::getEntity( const Handle handle ) {
	if ( handle._handle >= 0xFFFFFFFDu )
		return nullptr;

	const auto chunk_index = ( handle._handle & 0x7FFFu ) >> 9u;

	const auto chunk = *Mem{ this }.offset( 0x8 * chunk_index + 0x10 ).as< Mem * >( );
	if ( !chunk )
		return nullptr;

	const auto slot_index = handle._handle & 0x1FFu;

	return *chunk.offset( 0x78 * slot_index ).as< BaseEntity ** >( );
}

inline valve::EntityIdentity *valve::EntitySystem::getIdentity( const std::uint32_t idx ) {
	const auto chunk = *Mem{ this }.offset( 0x8 * ( idx >> 9u ) + 0x10 ).as< Mem * >( );
	if ( !chunk )
		return nullptr;

	return chunk.offset( 0x78 * idx ).as< EntityIdentity * >( );
}

inline valve::EntityIdentity *valve::EntitySystem::getIdentity( const Handle handle ) {
	if ( handle._handle >= 0xFFFFFFFDu )
		return nullptr;

	const auto chunk_index = ( handle._handle & 0x7FFFu ) >> 9u;

	const auto chunk = *Mem{ this }.offset( 0x8 * chunk_index + 0x10 ).as< Mem * >( );
	if ( !chunk )
		return nullptr;

	const auto slot_index = handle._handle & 0x1FFu;

	return chunk.offset( 0x78 * slot_index ).as< EntityIdentity* >( );
}

inline void valve::EntitySystem::forEachIdentity( const std::function< bool( EntityIdentity * ) > &fn ) {
	auto start = getEntity( 0u )->getIdentity( );
	if ( !start )
		return;

	for ( ; start->getPrevNode( ); start = start->getPrevNode( ) )
		;

	for ( auto node = start; node; node = node->getNextNode( ) )
		if ( fn( node ) )
			return;
}

inline valve::SwapChainDx11 *valve::RenderDeviceDx11::getSwapchain( ) {
	const auto swapchain_holder = *Mem{ this }.offset( 0x1E688 ).as< Mem * >( );
	if ( !swapchain_holder )
		return nullptr;

	return *swapchain_holder.offset( 0x10 ).as<SwapChainDx11 **>( );
}

template < typename _Target >
inline _Target *valve::Handle::resolve( ) const {
	return _entitySystem->getEntity( *this )->as< _Target >( );
}