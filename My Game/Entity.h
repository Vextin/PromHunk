/// \file Entity.h
#ifndef __L4RC_GAME_ENTITY_H__
#define __L4RC_GAME_ENTITY_H__

#include "Object.h"

///Base class for all enemies and player
///Must implement move() and draw()
class CEntity :
    public CObject
{
protected:
    float health = 0;
public:
    CEntity(eSprite t, const Vector2&); //constructor
    virtual bool TakeDamage(int d); //This entity should take d damage. Returns true if the entity is now dead or false if the enemy is still alive.
    virtual void Die();
};

#endif //__L4RC_GAME_ENTITY_H__