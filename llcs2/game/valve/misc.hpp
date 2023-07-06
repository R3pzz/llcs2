#pragma once

namespace valve {
	template < typename _Contained >
	class UtlTsHash {
		typedef
			_Contained
			ContainedType;

		typedef
			std::uint64_t
			KeyType;

		struct Container {
			Container				*_next{};
			std::uint8_t		$align0[ 8u ]{};
			ContainedType		_data{};
		};

		struct ContainerHeader {
			ContainerHeader *_next{};
			std::size_t			_hash{};
			Container				_blockList[ 256u ]{};
		};

		struct Bucket {
			std::uint8_t		$align0[ 24u ]{};
			ContainerHeader *_container{};
		};

	public:
		int								_blockSize{}, _blocksPerBlob{},
											_growType, _blocksAllocated{},
											_size{}, _peakAlloc{};

		Bucket						_bucket{};

		inline constexpr UtlTsHash( ) = default;

		inline void forEachElement( const std::function< bool( ContainedType ) > &fn ) const;
	};
}

#include "misc.inline.inl"