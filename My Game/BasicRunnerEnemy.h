/// \file BasicShooterEnemy.h
/// \brief Interface for the BasicShooterEnemy object class CBasicRunnerEnemy.

#ifndef __L4RC_GAME_BasicRunnerEnemy_H__
#define __L4RC_GAME_BasicRunnerEnemy_H__

#include "RangedWeapon.h"	//TODO: Change for meleeweapon
#include "Enemy.h"
#include <stack>

// Creating a shortcut for int, int pair type
typedef std::pair<int, int> Pair;

/// \brief The BasicRunnerEnemy object. 
///
/// CBasicRunnerEnemy is the abstract representation of a BasicRunnerEnemy object.

class CBasicRunnerEnemy : public CEnemy {
protected:
	void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
	void RotateTowardsAndMove(const Vector2&);  ///< Move towards player
	float PathFindCooldown = 2.0f;
public:
	CRangedWeapon* weapon;

	CBasicRunnerEnemy(const Vector2& p); ///< Constructor.
	~CBasicRunnerEnemy();///Deconstructor

	void move() override; ///< Move BasicRunnerEnemy.

	std::stack<Pair> path2player; // stack with path to player
	void calcPath(); // calc path to player
}; //CBullet

#endif //__L4RC_GAME_BasicRunnerEnemy_H__