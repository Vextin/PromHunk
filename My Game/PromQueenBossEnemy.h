/// \file BasicShooterEnemy.h
/// \brief Interface for the BasicShooterEnemy object class CPromQueenEnemy.

#ifndef __L4RC_GAME_PromQueenEnemy_H__
#define __L4RC_GAME_PromQueenEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Enemy.h"

/// \brief The PromQueenEnemy object. 
///
/// CPromQueenEnemy is the abstract representation of a PromQueenEnemy object.

class CPromQueenEnemy : public CEnemy {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player

public:
	CRangedWeapon* weapon;

	CPromQueenEnemy(const Vector2& p); ///< Constructor.
	~CPromQueenEnemy();///Deconstructor

	void move() override; ///< Move PromQueenEnemy.
}; //CBullet

#endif //__L4RC_GAME_PromQueenEnemy_H__