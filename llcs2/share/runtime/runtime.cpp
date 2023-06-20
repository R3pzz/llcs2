#include <share/share.hpp>

void Runtime::store_loaded_images( const bool debug ) {
	auto peb = x64::Peb::get( );

	peb->_loader->for_each_entry(
		[ debug, this ]( const x64::LoaderEntry *entry ) -> bool {
			if ( !entry ) {
				return false;
			}

			x64::ImageDesc desc{ entry->_image_base };

			_image_dict.insert_or_assign( hash( entry->_base_dll_name.str( ).c_str( ) ), desc );

			if ( debug ) {
				std::wcout << L"[runtime.Runtime.store_loaded_images]: found a PE image named "
					<< entry->_base_dll_name.str( ) << std::endl;
			}

			return false;
		}
	);
}

void Runtime::extract_interfaces( const bool debug ) {
	std::for_each( _image_dict.begin( ), _image_dict.end( ),
		[ debug, this ]( ImageDictionary::value_type pair ) {
			const auto &image = pair.second;

			for ( auto desc = game::InterfaceDesc::first( image ); desc; desc = desc->_next ) {
				_interface_dict.insert_or_assign( hash( desc->_name ), desc->_getter( ) );

				if ( debug ) {
					std::cout << "[Runtime.extract_interfaces]: found an interface named "
						<< desc->_name << std::endl;
				}
			}
		}
	);
}

void Runtime::init( ) {
	std::FILE *confile{};

	AllocConsole( );
	AttachConsole( ATTACH_PARENT_PROCESS );

	freopen_s( &confile, "CONOUT$", "w", stdout );

	store_loaded_images( true );

	extract_interfaces( true );

	std::fclose( confile );

	FreeConsole( );
}