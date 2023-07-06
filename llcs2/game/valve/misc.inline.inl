#pragma once

template < typename _Contained >
inline void valve::UtlTsHash< _Contained >::forEachElement(
	const std::function< bool( ContainedType ) > &fn
) const {
	std::size_t i{};
	
	for ( auto header = _bucket._container; header; header = header->_next )
		for ( std::size_t j{}; i < _size && j < 256u; i++, j++ )
			if ( fn( header->_blockList[ i ]._data ) )
				return;
}