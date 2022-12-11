/// \file Obstacle.h
#ifndef __L4RC_GAME_OBSTACLE_H__
#define __L4RC_GAME_OBSTACLE_H__

#include "Entity.h"

///Base class for all world obstacles

class CObstacle :
    public CEntity
{
protected:
    float baseHealth = 10.0f;
public:
    CObstacle(eSprite t, const Vector2&); //constructor
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.
    virtual bool TakeDamage(float d); //This should take d damage. Returns true if the entity is now dead or false if the enemy is still alive.
    virtual void Die();
    virtual void Update();

    float health;

};

#endif //__L4RC_GAME_OBSTACLE_H__