/// \file CheerleaderEnemy.h
/// \brief Interface for the CheerleaderEnemy object class CheerleaderEnemy.

#ifndef __L4RC_GAME_CheerleaderEnemy_H__
#define __L4RC_GAME_CheerleaderEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Entity.h"

/// \brief The CheerleaderEnemy object. 
///
/// CheerleaderEnemy is the abstract representation of a CheerleaderEnemy object.

class CCheerleaderEnemy : public CEntity {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player
	void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.

	float BuffCooldown = 0.0f;
	void CheerBuff(std::list<CObject*>);

public:
	CRangedWeapon* weapon;

	CCheerleaderEnemy(const Vector2& p); ///< Constructor.
	~CCheerleaderEnemy();///Deconstructor

	void move() override; ///< Move CheerleaderEnemy
}; //CBullet

#endif //__L4RC_GAME_CheerleaderEnemy_H__