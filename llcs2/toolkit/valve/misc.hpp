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

		struct FixedData {
			KeyType						_key{};
			FixedData					*_next{};
			ContainedType			_data{};
		};

		struct FixedStructData {
			ContainedType			_data{};
			KeyType						_key{};
		};

		struct StructData {
			std::uint8_t			$align0[ 16u ]{};
			FixedStructData		_list[ 256u ]{};
		};

		struct BucketData {
			ContainedType			_data{};
			FixedData					*_next{};
			KeyType						_key{};
		};

		struct UnallocatedData {
			UnallocatedData		*_next{};
			std::uint8_t			$align0[ 24u ]{};
			BucketData				_blockList[ 256u ]{};
		};

		struct Bucket {
			StructData				*_structData{};
			std::uint8_t			$align0[ 8u ]{};
			AllocatedData			*_allocatedData{};
			UnallocatedData		*_unallocatedData{};
		};

	public:
		int									_blockSize{}, _blocksPerBlob{},
												_growType, _blocksAllocated{},
												_size{}, _peakAlloc{};

		Bucket							_bucket{};
		bool								_needsCommit{};

		inline constexpr UtlTsHash( ) = default;

		inline void forEachElement( const std::function< bool( ContainedType ) > &fn ) const;
	};
}

#include "misc.inline.inl"