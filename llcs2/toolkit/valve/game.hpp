#pragma once

namespace valve {
	struct SchemaTypeScope {
		struct SchemaType {
			Mem						_vtable{};
			const char		*_name{};
		};

		struct ClassBinding {
			ClassBinding	*_parent{};

			const char		*_binName{},
										*_moduleName{},
										*_className{};

			std::uint8_t	$align0[ 24u ]{};

			SchemaType		*_schemaType{};
		};

		struct TypeInfo {
			std::uint8_t	$align0[ 8u ]{};

			const char		*_name{};
		};

		struct FieldInfo {
			const char		*_name{};
			TypeInfo			*_typeInfo{};
			std::uint16_t	_offset{};

			std::uint8_t	$align0[ 14u ]{};
		};

		struct ClassInfo {
			std::uint8_t	$align0[ 8u ]{};
			
			const char		*_name{}, *_module{};
			std::uint32_t	_size{};
			std::uint16_t _fieldSize{},
										_staticSize{},
										_metadataSize{};

			std::uint8_t	$align1[ 6u ]{};

			FieldInfo			*_fields{};
		};

		typedef
			UtlTsHash< ClassBinding * >
			BindingTable;

		std::uint8_t		$align0[ 8u ]{};

		char						_name[ 256u ]{};

		std::uint8_t		$align1[ 1104u ]{};

		BindingTable		_bindings{};

		_LLCS2_INTERFACE( findClass( const char *name ),
			_LLCS2_INTERF_CONV( ClassInfo *, const char * ), 2u, name );
	};
}