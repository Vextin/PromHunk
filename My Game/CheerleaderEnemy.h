/// \file CheerleaderEnemy.h
/// \brief Interface for the CheerleaderEnemy object class CheerleaderEnemy.

#ifndef __L4RC_GAME_CheerleaderEnemy_H__
#define __L4RC_GAME_CheerleaderEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Enemy.h"

/// \brief The CheerleaderEnemy object. 
///
/// CheerleaderEnemy is the abstract representation of a CheerleaderEnemy object.

class CCheerleaderEnemy : public CEnemy {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player

	float BuffCooldown = 10.0f;

public:
	CRangedWeapon* weapon;

	CCheerleaderEnemy(const Vector2& p); ///< Constructor.
	~CCheerleaderEnemy();///Deconstructor

	void CheerBuff(std::list<CObject*>);
	void move() override; ///< Move CheerleaderEnemy
}; //CBullet

#endif //__L4RC_GAME_CheerleaderEnemy_H__