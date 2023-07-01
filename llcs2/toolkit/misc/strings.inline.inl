#pragma once

inline auto toNarrow(
	const std::wstring_view str
) {
	if ( str.empty( ) )
		return std::string{};

	const auto new_len = WideCharToMultiByte( CP_UTF8, 0, str.data( ), str.size( ), nullptr, 0, nullptr, nullptr );
	if ( !new_len )
		return std::string{};

	std::string narrow{};

	narrow.reserve( new_len );

	WideCharToMultiByte( CP_UTF8, 0, str.data( ), str.size( ), narrow.data( ), new_len, nullptr, nullptr );

	return narrow;
}

inline auto toWide( 
	const std::string_view str
) {
	if ( str.empty( ) )
		return std::wstring{};

	const auto new_len = MultiByteToWideChar( CP_UTF8, 0ul, str.data( ), -1, nullptr, 0 );
	if ( !new_len )
		return std::wstring{};

	std::wstring wide{};

	wide.reserve( new_len );

	MultiByteToWideChar( CP_UTF8, 0ul, str.data( ), -1, wide.data( ), new_len );

	return wide;
}