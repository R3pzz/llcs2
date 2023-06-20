#pragma once

namespace x64 {
  inline constexpr auto DosHdr::nt( ) const {
    return Address{ this }.offset( _nt_reloc ).as<NtHdr *>( );
  }

  inline void LoaderData::for_each_entry( const std::function<bool( LoaderEntry * )> &closure ) {
    for ( auto link = _in_load_module_list.Flink; link; link = link->Flink ) {
      auto entry = CONTAINING_RECORD( link, LoaderEntry, _in_load_module_list );

      if ( !entry ) {
        continue;
      }

      if ( closure( entry ) ) {
        break;
      }
    }
  }

  inline void LoaderData::for_each_entry( const std::function<bool( const LoaderEntry * )> &closure ) const {
    for ( auto link = _in_load_module_list.Flink; link != _in_load_module_list.Flink; link = link->Flink ) {
      const auto entry = CONTAINING_RECORD( link, LoaderEntry, _in_load_module_list );

      if ( !entry ) {
        continue;
      }

      if ( closure( entry ) ) {
        break;
      }
    }
  }

  inline constexpr auto UnicodeString::str( ) const {
    return std::wstring{ _str, _length / sizeof( wchar_t ) };
  }

  inline Peb *Peb::get( ) {
    return reinterpret_cast<Peb *>( __readgsqword( 0x60ul ) );
  }

  inline constexpr auto ImageDesc::dos_hdr( ) const {
    return _base.as<x64::DosHdr *>( );
  }

  inline constexpr auto ImageDesc::nt_hdr( ) const {
    return _base.as<x64::DosHdr *>( )->nt( );
  }

  inline constexpr auto ImageDesc::end( ) const {
    return _base + nt_hdr( )->_opt64._img_size;
  }

  inline constexpr auto ImageDesc::operator!( ) const {
    return !_base;
  }

  inline constexpr auto &ImageDesc::operator=( const HMODULE other ) {
    _base = Address{ other };

    return *this;
  }

  inline auto ImageDesc::query_export( const std::string_view name ) const {
    return Address{ GetProcAddress( _base.as<HMODULE>( ), name.data( ) ) };
  }

  inline auto ImageDesc::try_find( const std::string_view name ) {
    return ImageDesc{ GetModuleHandle( name.data( ) ) };
  }
}