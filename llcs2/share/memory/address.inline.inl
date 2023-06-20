#pragma once

namespace detail {
	template <typename _Size>
		requires std::is_integral_v<_Size>
	template <typename _Type>
	inline constexpr auto AddressBase<_Size>::as( ) const {
		if constexpr ( IsDirectCastable<_Type> ) {
			/* if we can cast it directly
				 (meaning the same primitive kind),
				 apply a static_cast */
			return static_cast<_Type>( _ptr );
		}
		else {
			/* else, reinterpret_cast */
			return reinterpret_cast<_Type>( _ptr );
		}
	}

	template <typename _Size>
		requires std::is_integral_v<_Size>
	inline constexpr auto &AddressBase<_Size>::offset_self( const DiffType v ) {
		_ptr += v;

		return *this;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::offset( const DiffType v ) const {
		return AddressBase<SizeType>{ _ptr + v };
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator+( const DiffType v ) const {
		return AddressBase<SizeType>{ _ptr + v };
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator-( const DiffType v ) const {
		return AddressBase<SizeType>{ _ptr - v };
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator*( const DiffType v ) const {
		return AddressBase<SizeType>{ _ptr *v };
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator/( const DiffType v ) const {
		return AddressBase<SizeType>{ _ptr / v };
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator<( const AddressBase<SizeType> &other ) const {
		return _ptr < other._ptr;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator>( const AddressBase<SizeType> &other ) const {
		return _ptr > other._ptr;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator<=( const AddressBase<SizeType> &other ) const {
		return _ptr <= other._ptr;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator>=( const AddressBase<SizeType> &other ) const {
		return _ptr >= other._ptr;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto AddressBase<_Size>::operator!( ) const {
		return !_ptr;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto &AddressBase<_Size>::operator++( ) {
		_ptr++;

		return *this;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto &AddressBase<_Size>::operator++( int ) {
		++_ptr;

		return *this;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto &AddressBase<_Size>::operator--( ) {
		_ptr--;

		return *this;
	}

	template <typename _Size>
	requires std::is_integral_v<_Size>
		inline constexpr auto &AddressBase<_Size>::operator--( int ) {
		--_ptr;

		return *this;
	}
}