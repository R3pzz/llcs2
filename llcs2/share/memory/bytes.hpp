#pragma once

struct ByteString : std::string_view {
	inline constexpr ByteString( ) = default;

	inline constexpr ByteString( const char *str )
		: std::string_view{ str } {}

	inline constexpr ByteString( const std::string_view str )
		: std::string_view{ str } {}

	inline constexpr ByteString( const std::string str )
		: std::string_view{ str } {}

	inline consteval std::size_t bytenum( ) const;

	inline static consteval std::size_t bytenum( const std::string_view str );
};

template <std::size_t _Length>
struct ByteSequence {
	struct ByteDescriptor {
		enum struct ByteType : std::uint32_t {
			kRegular = 0u,
			kWildcard = 1u,
		} _type{ ByteType::kRegular };

		std::uint8_t _val{};

		inline constexpr ByteDescriptor( ) = default;

		inline constexpr ByteDescriptor( char first ) {
			_type = ByteType::kWildcard;
		}

		inline constexpr ByteDescriptor( const char first, const char second ) {
			_val = static_cast<std::uint8_t>( b2i( first ) * 0x10u + b2i( second ) );
		}

		inline static constexpr auto b2i( const std::size_t b );
	};

	using ByteArray = std::array< ByteDescriptor, _Length >;

	ByteArray _arr{};

	inline constexpr ByteSequence( ) = default;

	inline constexpr ByteSequence( const ByteArray &arr )
		: _arr{ arr } {}

	inline constexpr ByteSequence( const ByteString &sig ) {
		parse( sig );
	}

	inline constexpr void parse( const std::string_view seq );

	inline Address seek( const Address start, const Address end ) const;
};

#include "bytes.inline.inl"