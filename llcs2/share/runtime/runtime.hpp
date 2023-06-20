#pragma once

class Runtime {
	using ImageDictionary = std::unordered_map<std::size_t, x64::ImageDesc>;
	using InterfaceDictionary = std::unordered_map<std::size_t, Address>;
	using RecvNodeDictionary = std::unordered_map<std::size_t, game::RecvTable::Node *>;

private:
	/* all loaded PE images are here */
	ImageDictionary _image_dict{};

	/* all interfaces we've managed to find are here */
	InterfaceDictionary _interface_dict{};

	/* grab all PE images and their base addresses */
	void store_loaded_images( const bool debug = false );

	/* extrarct all the interfaces from every PE image found */
	void extract_interfaces( const bool debug = false );

public:
	inline constexpr Runtime( ) = default;
	
	void init( );
};

inline const auto runtime = std::make_unique<Runtime>( );

#include "runtime.inline.inl"