#pragma once

namespace x64 {
#pragma pack( push, 4 )
  struct DataDir {
    ulong_t         _va{};
    ulong_t         _size{};
  };

  static_assert( sizeof( DataDir ) == sizeof( IMAGE_DATA_DIRECTORY ),
    "sizes of x64::DataDir and IMAGE_DATA_DIRECTORY mismatch" );

  struct CoffHdr {
    std::uint16_t   _machine{};
    std::uint16_t   _sections_cnt{};
    ulong_t         _dt_stamp{};
    ulong_t         _sym_table_ptr;
    ulong_t         _sym_cnt{};
    std::uint16_t   _opt_hdr_size{};
    std::uint16_t   _characteristics{};
  };

  static_assert( sizeof( CoffHdr ) == sizeof( IMAGE_FILE_HEADER ),
    "sizes of x64::CoffHdr and IMAGE_FILE_HEADER mismatch" );

  struct OptHdr {
    std::uint16_t   _magic{};

    union {
      std::uint16_t _link_ver{};

      struct {
        std::uint8_t _link_ver_maj;
        std::uint8_t _link_ver_min;
      };
    };

    ulong_t         _code_size{};
    ulong_t         _inited_data_size{};
    ulong_t         _uninited_data_size{};
    Address         _entry_point{};
    Address         _base_of_code{};
    Address         _base_of_data{};
    Address         _base_of_img{};
    ulong_t         _sec_align{};
    ulong_t         _file_align{};

    union {
      std::uint32_t _os_ver{};

      struct {
        std::uint16_t _os_ver_maj;
        std::uint16_t _os_ver_min;
      };
    };

    union {
      std::uint32_t _img_ver{};

      struct {
        std::uint16_t _img_ver_maj;
        std::uint16_t _img_ver_min;
      };
    };

    union {
      std::uint32_t _subsys_ver{};

      struct {
        std::uint16_t _subsys_ver_maj;
        std::uint16_t _subsys_ver_min;
      };
    };

    ulong_t         _win32_ver{};
    ulong_t         _img_size{};
    ulong_t         _hdrs_size{};
    ulong_t         _checksum{};
    std::uint16_t   _subsys{};
    std::uint16_t   _dll_characs{};
    std::uint32_t   _stack_res_size{};
    std::uint32_t   _stack_commit_size{};
    std::uint32_t   _heap_res_size{};
    std::uint32_t   _heap_commit_size{};
    ulong_t         _ldr_flags{};
    ulong_t         _rva_count{};

    union {
      DataDir       _table[ 16u ]{};

      struct {
        DataDir     _exp;
        DataDir     _imp;
        DataDir     _res;
        DataDir     _exception;
        DataDir     _sec;
        DataDir     _basereloc;
        DataDir     _dbg;
        DataDir     _arch;
        DataDir     _gp;
        DataDir     _tls;
        DataDir     _ldcfg;
        DataDir     _bound_imp;
        DataDir     _iat;
        DataDir     _delay_imp;
        DataDir     _com_desc;
      };
    } _data_dirs{};
  };

  static_assert( sizeof( OptHdr ) == sizeof( IMAGE_OPTIONAL_HEADER64 ),
    "sizes of x64::CoffHdr and IMAGE_FILE_HEADER mismatch" );

  struct NtHdr {
    ulong_t _sig{};
    CoffHdr _coff{};
    OptHdr _opt64{};
  };

  static_assert( sizeof( NtHdr ) == sizeof( IMAGE_NT_HEADERS64 ),
    "sizes of x64::nt64_hdr_t and IMAGE_NT_HEADERS64 mismatch" );

  struct DosHdr {
    std::uint16_t   _magic{};
    std::uint16_t   _cblp{};
    std::uint16_t   _cp{};
    std::uint16_t   _crlc{};
    std::uint16_t   _cparhdr{};
    std::uint16_t   _minalloc{};
    std::uint16_t   _maxalloc{};
    std::uint16_t   _ss{};
    std::uint16_t   _sp{};
    std::uint16_t   _csum{};
    std::uint16_t   _ip{};
    std::uint16_t   _cs{};
    std::uint16_t   _lfarlc{};
    std::uint16_t   _ovno{};
    std::uint16_t   _res[ 4u ]{};
    std::uint16_t   _oemid{};
    std::uint16_t   _oeminfo{};
    std::uint16_t   _res2[ 10u ]{};
    long            _nt_reloc{};

    inline constexpr auto nt( ) const;
  };

  static_assert( sizeof( DosHdr ) == sizeof( IMAGE_DOS_HEADER ),
    "sizes of x64::dos_hdr_t and IMAGE_DOS_HEADER mismatch" );

  struct UnicodeString {
    std::uint16_t   _length{};
    std::uint16_t   _max_length{};
    wchar_t         *_str{};

    inline constexpr auto str( ) const;
  };

  struct LoaderEntry {
    LIST_ENTRY    _in_load_module_list{};
    LIST_ENTRY    _in_memory_module_list{};
    LIST_ENTRY    _in_init_module_list{};
    Address       _image_base{};
    Address       _entry_point{};
    std::uint32_t _image_size{};
    UnicodeString _full_dll_name{};
    UnicodeString _base_dll_name{};
  };

  struct LoaderData {
    std::uint32_t _length{};
    std::uint8_t  _initialized{};
    Address       _ss_handle{};
    LIST_ENTRY    _in_load_module_list{};
    LIST_ENTRY    _in_memory_module_list{};
    LIST_ENTRY    _in_init_module_list{};
    Address       _entry_in_progress{};
    std::uint8_t  _shutdown_in_progress{};
    std::uint64_t _shutdown_thread_id{};

    inline void for_each_entry( const std::function<bool( LoaderEntry * )> &closure );

    inline void for_each_entry( const std::function<bool( const LoaderEntry * )> &closure ) const;
  };

  struct Peb {
    std::uint8_t  pad0[ 2u ]{};
    std::uint8_t  _being_debugged{};
    std::uint8_t  _spare_bool{};
    Address       _mutant{};
    Address       _image_base{};
    LoaderData    *_loader{};

    inline static Peb *get( );
  };
#pragma pack( pop )

  struct ImageDesc {
    Address _base{};

    inline constexpr ImageDesc( ) = default;

    inline constexpr ImageDesc( const Address base )
      : _base{ base } {}

    inline constexpr ImageDesc( const HMODULE native )
      : _base{ native } {}

    inline constexpr auto dos_hdr( ) const;

    inline constexpr auto nt_hdr( ) const;

    inline constexpr auto end( ) const;

    inline constexpr auto operator!( ) const;

    inline constexpr auto &operator=( const HMODULE other );

    inline auto query_export( const std::string_view name ) const;

    inline static auto try_find( const std::string_view name );
  };
}

#include "native.inline.inl"