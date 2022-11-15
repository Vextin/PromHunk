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
    
    float speed = 50.0f;
    
    int flatDamageIncrease;
    float percentDamageIncrease;
    float percentSpeedIncrease;
    int flatHealthIncrease;
    float percentHealthIncrease;
    int flatAuraDamageIncrease;
    float percentAuraDamageIncrase;
public:
    CEntity(eSprite t, const Vector2&); //constructor
    virtual bool TakeDamage(int d); //This entity should take d damage. Returns true if the entity is now dead or false if the enemy is still alive.
    virtual void Die();
    float health = 5.0f;
    void SetFlatDamageIncrease(int d);
    void SetPercentDamageIncrease(float d);
    void SetFlatSpeedIncrease( float s);
    void SetPercentSpeedIncrease( float s);
    void SetFlatHealthIncrease(int h);
    void SetPercentHealthIncrease(float h );
    void SetFlatAuraDamageIncrease( int d);
    void SetFlatAuraIncrease(int r);
};

#endif //__L4RC_GAME_ENTITY_H__