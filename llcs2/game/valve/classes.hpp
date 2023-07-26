#pragma once

namespace valve {
	enum struct FrameStage : int {
		kUndefined = -1,
		kStart,
		kNetUpdateStart,
		kNetPostUpdateStart,
		kNetPostUpdateEnd,
		kNetUpdateEnd,
		kRenderStart,
		kRenderEnd,
	};

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

	/** Not sure about this thing and whether it's useful at all */
	struct MaterialParam {
		const char		*_name{},
									*_stringValue{};

		std::uint8_t	$align0[ 8u ]{};

		glm::vec4			_vecValue{};
		Mem						_texValue{};

		std::uint8_t	$align1[ 16u ]{};
	};

	struct Material {
		_LLCS2_INTERFACE( getName( ),
			_LLCS2_BUILD_CONV( const char * ), 0u );

		_LLCS2_INTERFACE( getNameWithMod( ),
			_LLCS2_BUILD_CONV( const char * ), 1u );

		_LLCS2_INTERFACE( findParameter( const char *name, MaterialParam **out ),
			_LLCS2_BUILD_CONV( bool, const char *, MaterialParam ** ), 23u, name, out );
	};

	struct MaterialDrawDesc {

	};

	struct SceneObjectDesc {

	};

	struct SceneLayer {

	};

	struct Handle {
		std::uint32_t		_handle{};
	};

	struct EntityIdentity {
		template < typename _OwnerType >
		_LLCS2_OFFSET_F( getOwner( ), _OwnerType *, 0x0 );

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

	struct GameSceneNode {
		_LLCS2_SCHEMA_F( getAbsOrigin( ),
			glm::vec3, "CGameSceneNode.m_vecAbsOrigin" );

		_LLCS2_SCHEMA_F( getOrigin( ),
			glm::vec3, "CGameSceneNode.m_vecOrigin" );

		_LLCS2_SCHEMA_F( getAbsRotation( ),
			glm::vec3, "CGameSceneNode.m_angAbsRotation" );
	};

	struct CollisionProperty {
		_LLCS2_SCHEMA_F( getMins( ),
			glm::vec3, "CCollisionProperty.m_vecMins" );

		_LLCS2_SCHEMA_F( getMaxs( ),
			glm::vec3, "CCollisionProperty.m_vecMaxs" );
	};

	struct GlowProperty {
		_LLCS2_SCHEMA_F( getType( ),
			int, "CGlowProperty.m_iGlowType" );

		_LLCS2_SCHEMA_F( getColor( ),
			glm::vec4, "CGlowProperty.m_glowColorOverride" );

		_LLCS2_SCHEMA_F( isFlashing( ),
			bool, "CGlowProperty.m_bFlashing" );

		_LLCS2_SCHEMA_F( isGlowing( ),
			bool, "CGlowProperty.m_bGlowing" );
	};

	struct EntityInstance {
		template < typename _CastType >
		inline constexpr _CastType *as( );

		template < typename _CastType >
		inline constexpr const _CastType *as( ) const;

		_LLCS2_INTERFACE( isPlayerController( ),
			_LLCS2_BUILD_CONV( bool ), 139u );

		_LLCS2_INTERFACE( isPlayerPawn( ),
			_LLCS2_BUILD_CONV( bool ), 142u );

		_LLCS2_SCHEMA_F( getIdentity( ),
			EntityIdentity *, "CEntityInstance.m_pEntity" );
	};

	struct BaseEntity : EntityInstance {
		inline glm::vec4 healthAsColor( );

		_LLCS2_SCHEMA_F( getSceneNode( ),
			GameSceneNode *, "C_BaseEntity.m_pGameSceneNode" );

		_LLCS2_SCHEMA_F( getCollisionProperty( ),
			CollisionProperty *, "C_BaseEntity.m_pCollision" );

		_LLCS2_SCHEMA_F( getHealth( ),
			int, "C_BaseEntity.m_iHealth" );
	};

	struct ModelEntity : BaseEntity {
		_LLCS2_SCHEMA_F( getGlowProperty( ),
			GlowProperty, "C_BaseModelEntity.m_Glow" );
	};

	struct BaseAnimGraph : ModelEntity {

	};

	struct BaseFlex : BaseAnimGraph {

	};

	struct BaseCombatCharacter : BaseFlex {

	};

	struct PlayerController;

	struct BasePlayerPawn : BaseCombatCharacter {
		_LLCS2_SCHEMA_F( getController( ),
			Handle, "C_BasePlayerPawn.m_hController" );
	};

	struct CSPlayerPawn : BasePlayerPawn {
		
	};

	struct PlayerController : BaseEntity {
		_LLCS2_SCHEMA_F( getPawnHandle( ),
			Handle, "CBasePlayerController.m_hPawn" );

		_LLCS2_SCHEMA_F_PTR( getPlayerName( ),
			char, "CBasePlayerController.m_iszPlayerName" );
	};

	struct CSPlayerController : PlayerController {

	};
}

#include "classes.inline.inl"