/// \file Enemy.h
#ifndef __L4RC_GAME_ENEMY_H__
#define __L4RC_GAME_ENEMY_H__

#include "Entity.h"

///Base class for all enemies
class CEnemy :
	public CEntity
{
protected:
public:
	CEnemy(eSprite t, const Vector2&); //constructor
	virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.
};

#endif //__L4RC_GAME_ENEMY_H__
