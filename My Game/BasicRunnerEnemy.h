/// \file BasicShooterEnemy.h
/// \brief Interface for the BasicShooterEnemy object class CBasicShooterEnemy.

#ifndef __L4RC_GAME_BasicRunnerEnemy_H__
#define __L4RC_GAME_BasicRunnerEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Entity.h"

/// \brief The BasicShooterEnemy object. 
///
/// CBasicShooterEnemy is the abstract representation of a BasicShooterEnemy object.

class CBasicRunnerEnemy : public CEntity {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player
	void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.

public:
	CRangedWeapon* weapon;

	CBasicRunnerEnemy(const Vector2& p); ///< Constructor.
	~CBasicRunnerEnemy();///Deconstructor

	void move() override; ///< Move BasicShooterEnemy.
}; //CBullet

#endif //__L4RC_GAME_BasicShooterEnemy_H__