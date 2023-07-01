#pragma once

inline consteval std::size_t ByteString::bytenum( ) const {
	std::size_t res{};

	for ( std::size_t it{}; it < size( ); it += 2u ) {
		if ( at( it ) == '?' )
			res++;
		else
			res++, it++;
	}

	return res;
}

inline consteval std::size_t ByteString::bytenum( const std::string_view str ) {
	std::size_t res{};

	for ( std::size_t it{}; it < str.size( ); it += 2u ) {
		if ( str.at( it ) == '?' )
			res++;
		else
			res++, it++;
	}

	return res;
}

template < std::size_t _Length >
	requires ( _Length > 0ull )
inline constexpr auto ByteSequence< _Length >::ByteDescriptor::b2i( const std::size_t b ) {
	if ( b >= '0' && b <= '9' )
		return b - '0';

	if ( b >= 'A' && b <= 'F' )
		return b - 'A' + 10u;

	return b - 'a' + 10u;
}

template < std::size_t _Length >
	requires ( _Length > 0ull )
inline constexpr void ByteSequence<_Length>::parse( const std::string_view seq ) {
	std::size_t j{};

	for ( std::size_t i{}; i < seq.size( ); i += 2u ) {
		if ( seq.at( i ) == '?' ) {
			_arr.at( j ) = ByteDescriptor{ '?' };
			j++;
		}
		else {
			_arr.at( j ) = ByteDescriptor{ seq.at( i ), seq.at( ++i ) };
			j++;
		}
	}
}

template < std::size_t _Length >
	requires ( _Length > 0ull )
inline Mem ByteSequence< _Length >::seek( const Mem start, const Mem end ) const {
	if ( _arr.empty( ) )
		return Mem{};

	for ( auto i = start; i < end; i++ ) {
		auto found = true;

		for ( std::size_t j{}; j < _arr.size( ); j++ ) {
			auto byte = *i.offset( j ).as<std::uint8_t *>( );

			if ( _arr.at( j )._val == byte
				|| _arr.at( j )._type == ByteDescriptor::ByteType::kWildcard )
				continue;

			found = false;

			break;
		}

		if ( found )
			return i;
	}

	return Mem{};
}