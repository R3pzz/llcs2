#pragma once

namespace valve {
	struct SchemaTypeScope {
		struct SchemaType {
			Mem						_vtable{};
			const char		*_name{};
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

		struct ClassBinding {
			ClassBinding	*_parent{};
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

		_LLCS2_INTERFACE( findBinding( const char *name ),
			_LLCS2_BUILD_CONV( ClassBinding *, const char * ), 2u, name );
	};

	struct Handle {
		std::uint32_t		_handle{};
	};

	struct EntityIdentity {
		_LLCS2_SCHEMA_F( getDesignerName( ),
			const char *, "CEntityIdentity.m_designerName" );

		_LLCS2_SCHEMA_F( getWorldGroup( ),
			std::uint32_t, "CEntityIdentity.m_worldGroupId" );

		_LLCS2_SCHEMA_F( getFlags( ),
			std::uint32_t, "CEntityIdentity.m_flags" );

		_LLCS2_SCHEMA_F( getPrevNode( ),
			EntityIdentity *, "CEntityIdentity.m_pPrev" );

		_LLCS2_SCHEMA_F( getNextNode( ),
			EntityIdentity *, "CEntityIdentity.m_pNext" );
	};

	struct EntityInstance {
		_LLCS2_SCHEMA_F( getIdentity( ),
			EntityIdentity *, "CEntityInstance.m_pEntity" );
	};

	struct BaseEntity : EntityInstance {

	};

	struct ModelEntity : BaseEntity {

	};

	struct BaseAnimGraph : ModelEntity {

	};

	struct BaseFlex : BaseAnimGraph {

	};

	struct BaseCombatCharacter : BaseFlex {

	};

	struct BasePlayerPawn : BaseCombatCharacter {
		
	};

	struct CSPlayerPawn : BasePlayerPawn {
		
	};

	struct PlayerController : BaseEntity {
		_LLCS2_SCHEMA_F( getPawnHandle( ),
			Handle, "CBasePlayerController.m_hPawn" );
	};

	struct CSPlayerController : PlayerController {

	};
}