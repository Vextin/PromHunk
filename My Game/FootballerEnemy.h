/// \file FootballerEnemy.h
/// \brief Interface for the FootballerEnemy object class FootballerEnemy.

#ifndef __L4RC_GAME_FootballerEnemy_H__
#define __L4RC_GAME_FootballerEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Enemy.h"

/// \brief The FootballerEnemy object. 
///
/// FootballerEnemy is the abstract representation of a FootballerEnemy object.

class CFootballerEnemy : public CEnemy {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player

	float SprintCooldown = 10.0f;

public:
	CRangedWeapon* weapon;

	CFootballerEnemy(const Vector2& p); ///< Constructor.
	~CFootballerEnemy();///Deconstructor

	void Sprint();
	void move() override; ///< Move FootballerEnemy
	virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.
}; //CBullet

#endif //__L4RC_GAME_FootballerEnemy_H__