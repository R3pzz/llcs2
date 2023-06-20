#pragma once

namespace game {
	template <class _Target>
		requires std::is_pointer_v<_Target>
	inline _Target InterfaceDesc::get( ) const {
		return _getter( ).as<_Target>();
	}

	template <class _Type>
		requires std::is_pointer_v<_Type>
	inline _Type InterfaceDesc::try_find( const std::string_view name ) const {
		for ( auto entry = this; entry; entry = entry->_next ) {
			if ( name.find( entry->_name ) != name.npos ) {
				return entry->get<_Type>( );
			}
		}

		return _Type{};
	}

	inline InterfaceDesc *InterfaceDesc::first( const x64::ImageDesc &image ) {
		const auto target = image.query_export( "CreateInterface" );

		if ( !target ) {
			return nullptr;
		}

		return target.offset( *target.offset( 0x3 ).as<std::uint32_t *>( ) ).as<InterfaceDesc *>( );
	}
}