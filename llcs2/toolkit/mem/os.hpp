#pragma once

namespace os {
	struct UniString {
		std::uint16_t			_length{},
											_maxLength{};

		wchar_t						*_data{};

		inline constexpr UniString( ) = default;

		inline auto wstr( ) const;
	};

	struct LdrEntry {
		LIST_ENTRY				_inLoadLinks{},
											_inMemLinks{},
											_inInitLinks{};

		Mem								_dllBase{},
											_entryPoint{};
		std::uint32_t			_imageSize{};

		UniString					_fullDllName{},
											_baseDllName{};

		Bitfield< std::uint32_t > _flags{};

		std::uint16_t			_loadCount{},
											_tlsIndex{};

		LIST_ENTRY				_hashLinks{};
	};

	struct LdrData {
		inline void forEachInLoadEntry(
			const std::function< bool( LdrEntry * ) > &fn
		);

		std::uint32_t			_length{};
		std::uint8_t			_initialized{};
		std::uint8_t			$align0[ 3u ]{};

		Mem								_ssHandle{};

		LIST_ENTRY				_inLoadModules{},
											_inMemModules{},
											_inInitModules{};

		Mem								_inEntry{};
		std::uint8_t			_inShutdown{};

		std::uint8_t			$align1[ 3u ]{};
		Mem								_shutdownThreadId{};
	};

	struct Peb {
		std::uint8_t			_ias{}, _readImgFileEo{},
											_beingDebugged{};

		Bitfield< std::uint8_t > _bidField{};

		std::uint8_t			$align0[ 4u ]{};
		
		Mem								_mutant{}, _baseAddress{};

		LdrData						*_ldrData{};

		PRTL_USER_PROCESS_PARAMETERS _usrProcParams{};

		Mem								_subSysData{}, _heap{};

		PRTL_CRITICAL_SECTION _fastPebLock{};

		Mem								_sparePtr{}, _ifeoKey{};

		Bitfield< std::uint32_t > _crossProcessFlags{};

		std::uint8_t			$align1[ 4u ]{};

		Mem								_kernelCallbackTable{};

		/* the last is not to be rebuilt by now... */
	};

	inline auto peb( );
}

struct PeDesc {
	inline constexpr PeDesc( ) = default;

	inline constexpr PeDesc( const Mem base )
		: _base{ base }
	{}

	inline constexpr PeDesc( const HMODULE base )
		: _base{ base }
	{}

	inline auto dosHeader( ) const;

	inline auto ntHeader( ) const;

	inline auto size( ) const;

	inline auto start( ) const;

	inline auto end( ) const;

	Mem		_base{};
};

#include "os.inline.inl"