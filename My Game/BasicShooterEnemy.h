/// \file BasicShooterEnemy.h
/// \brief Interface for the BasicShooterEnemy object class CBasicShooterEnemy.

#ifndef __L4RC_GAME_BasicShooterEnemy_H__
#define __L4RC_GAME_BasicShooterEnemy_H__

#include "RangedWeapon.h"
#include "Enemy.h"

/// \brief The BasicShooterEnemy object. 
///
/// CBasicShooterEnemy is the abstract representation of a BasicShooterEnemy object.

class CBasicShooterEnemy: public CEnemy{
	protected:
		void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
		void RotateTowardsAndMove(const Vector2&);  ///< Move towards player
  
	public:
		CRangedWeapon* weapon;

		CBasicShooterEnemy(const Vector2& p); ///< Constructor.
		~CBasicShooterEnemy();///Deconstructor

		void move() override; ///< Move BasicShooterEnemy.
		void Update() override;
}; //CBullet

#endif //__L4RC_GAME_BasicShooterEnemy_H__