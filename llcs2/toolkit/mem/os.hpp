#pragma once

namespace os {
	struct uni_string_t {
		inline constexpr uni_string_t( ) = default;

		inline auto wstr( ) const;

		std::uint16_t			m_length{},
											m_max_length{};

		wchar_t						*m_data{};
	};

	struct ldr_entry_t {
		LIST_ENTRY				m_in_load_links{},
											m_in_mem_links{},
											m_in_init_links{};

		ptr_t							m_dll_base{},
											m_entry_point{};
		std::uint32_t			m_image_size{};

		uni_string_t			m_full_dll_name{},
											m_base_dll_name{};

		bitfield_t< std::uint32_t > m_flags{};

		std::uint16_t			m_load_count{},
											m_tls_idx{};

		LIST_ENTRY				m_hash_links{};
	};

	struct ldr_data_t {
		inline void for_each_in_load_entry(
			const std::function< bool( ldr_entry_t * ) > &fn );

		std::uint32_t			m_length{};

		std::uint8_t			m_initialized{};
		std::uint8_t			$align0[ 3u ]{};

		ptr_t							m_ss_handle{};

		LIST_ENTRY				m_in_load_modules{},
											m_in_mem_modules{},
											m_in_init_modules{};

		ptr_t							m_in_entry{};
		std::uint8_t			m_in_shutdown{};

		std::uint8_t			$align1[ 3u ]{};
		ptr_t							m_shutdown_thread_id{};
	};

	struct peb_t {
		std::uint8_t			m_ias{}, m_read_img_file_eo{},
											m_being_debugged{};

		bitfield_t< std::uint8_t > m_bit_field{};

		std::uint8_t			$align0[ 4u ]{};
		
		ptr_t							m_mutant{}, m_base_addr{};

		ldr_data_t				*m_ldr_data{};

		PRTL_USER_PROCESS_PARAMETERS m_user_proc_params{};

		ptr_t							m_subsys_data{}, m_heap{};

		PRTL_CRITICAL_SECTION m_fast_peb_lock{};

		ptr_t							m_spare_ptr{}, m_ifeo_key{};

		bitfield_t< std::uint32_t > m_cross_proc_flags{};

		std::uint8_t			$align1[ 4u ]{};

		ptr_t							m_kernel_cb_table{};

		/* the last is not to be rebuilt by now... */
	};

	inline auto peb( );
}

struct pe_desc_t {
	inline constexpr pe_desc_t( ) = default;

	inline constexpr pe_desc_t(
		const ptr_t base )
		: m_base{ base }
	{}

	inline constexpr pe_desc_t(
		const HMODULE base )
		: m_base{ base }
	{}

	inline auto dos_hdr( ) const;

	inline auto nt_hdr( ) const;

	inline auto size( ) const;

	inline auto start( ) const;

	inline auto end( ) const;

	ptr_t m_base{};
};

#include "os.inline.inl"