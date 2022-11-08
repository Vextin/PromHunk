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
    float health = 0.0f;
    float speed = 50.0f;
public:
    CEntity(eSprite t, const Vector2&); //constructor
};

#endif //__L4RC_GAME_ENTITY_H__