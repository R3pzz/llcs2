#pragma once

class EspSystem {
	struct EntityContext {
		valve::BaseEntity *_targetEntity{};

		struct {
			bool					_draw{};
			glm::vec4			_color{ 1.f, 1.f, 1.f, 1.f };
			bool					_outline{ true };
			glm::vec2			_position{};
			std::string		_text{};
		} _nameDrawInfo{};

		struct {
			enum : std::uint8_t {
				kStatic,
				kFade
			};

			bool					_draw{};
			glm::vec4			_color{ 1.f, 1.f, 1.f, 1.f };
			float					_thickness{ 1.f };
			std::uint8_t	_type{ kStatic };
			BoundingBox		_boundingBox{};
		} _healthDrawInfo{};

		struct {
			bool					_draw{};
			glm::vec4			_color{ 1.f, 1.f, 1.f, 1.f };
			bool					_outline{ true };
			BoundingBox		_boundingBox{};
		} _boxDrawInfo{};

		struct {

		} _debugDrawInfo{};

		inline constexpr EntityContext( ) = default;

		inline constexpr EntityContext( valve::BaseEntity *target )
			: _targetEntity{ target } {}
	};

	typedef
		std::list< EntityContext >
		ContextList;

	bool				_active{};
	ContextList	_contextList{};

	void pushName( const EntityContext &ctx ) const;

	void pushHealth( const EntityContext &ctx ) const;

	void pushBox( const EntityContext &ctx ) const;

	/** Maybe i'll have to move this thingy to rendersys/entity class itself.. */
	BoundingBox buildBoundingBox( valve::BaseEntity *entity ) const;

	inline bool storeContext( valve::EntityIdentity *identity );

public:
	inline constexpr EspSystem( ) = default;

	inline void setState( const bool to );

	inline bool getState( ) const;

	void onPresent( );
};

inline auto _espSystem = std::make_unique< EspSystem >( );

#include "espsys.inline.inl"