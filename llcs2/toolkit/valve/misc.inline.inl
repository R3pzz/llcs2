#pragma once

template < typename _Contained >
inline void valve::UtlTsHash< _Contained >::forEachElement(
	const std::function< bool( ContainedType ) > &fn
) const {
	std::size_t idx{};

	for ( auto data = _bucket._unallocatedData; data; data = data->_next )
		for ( std::size_t i{}; i < _blockSize && i != _size; i++, idx++ )
			if ( fn( data->_blockList[ i ]._data ) || idx >= _size )
				return;
}