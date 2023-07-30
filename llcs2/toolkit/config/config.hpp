#pragma once

namespace detail {
	template < typename _Type >
	static constexpr bool kIsConfigValue = std::_Is_any_of_v< _Type,
		bool, int, glm::vec4, float, const char *, const wchar_t *
	>;
}

class Config {
	struct Element {
		typedef
			std::array< std::uint8_t, 16u >
			SerializedBytes;

		std::size_t			_hash{};
		SerializedBytes _bytes{};

		inline constexpr Element( ) = default;

		inline constexpr Element( const std::size_t hash, const SerializedBytes &bytes )
			: _hash{ hash }, _bytes{ bytes }
		{}
	};

	typedef
		std::unordered_map< std::size_t,
			Element
		>
		ElementMap;

	std::filesystem::path _path{};
	ElementMap						_elements{};

	inline static bool isPathValid( const std::filesystem::path &path );

public:
	inline constexpr Config( ) = default;

	inline Config( const std::filesystem::path &path )
		: _path{ path } {}

	static constexpr auto kConfigExtension = L".cfg";

	template < typename _Type >
		requires detail::kIsConfigValue< _Type >
	inline _Type *getValueForWrite( const std::size_t name );

	template < typename _Type >
		requires detail::kIsConfigValue< _Type >
	inline _Type getValue( const std::size_t name );

	template < typename _Type >
		requires detail::kIsConfigValue< _Type >
	inline _Type setValue( const std::size_t name, const _Type &value );

	inline std::wstring_view getName( ) const;

	inline void setName( const std::wstring_view to );

	inline bool isEmpty( ) const;

	inline void clear( );

	bool saveToFile( );

	bool deleteFile( );

	static Config *loadFromFile( const std::filesystem::path &path );
};

#include "config.inline.inl"