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
    
    float baseDamage = 1.0f;
    float baseHealth = 3.0f;
    float baseSpeed = 100.0f;
    float baseAuraDamage = 0.0f;
    float baseAttackSpeed = 1.0f;
    int baseProjectileCount = 1; //number of bullets fired with each shot
    float baseProjectileSpeed = 400.0f;

    float flatDamageIncrease = 0.0f;
    float percentDamageIncrease = 0.0f;
    float flatSpeedIncrease = 0.0f;
    float percentSpeedIncrease = 0.0f;
    float flatAttackSpeedIncrease = 0.0f;
    float percentAttackSpeedIncrease = 0.0f;
    float flatHealthIncrease = 0.0f;
    float percentHealthIncrease = 0.0f;
    float flatAuraDamageIncrease = 0.0f;
    float percentAuraDamageIncrease = 0.0f;
    int flatProjectileCountIncrease = 0;
    float flatProjectileSpeedIncrease = 0.0f;
    float percentProjectileSpeedIncrease = 0.0f;

public:
    CEntity(eSprite t, const Vector2&); //constructor
    virtual bool TakeDamage(float d); //This entity should take d damage. Returns true if the entity is now dead or false if the enemy is still alive.
    virtual void Die();
    virtual void Update();
    float health;
    void SetFlatDamageIncrease(float d);
    void SetPercentDamageIncrease(float d);
    void SetFlatSpeedIncrease( float s);
    void SetPercentSpeedIncrease( float s);
    void SetFlatAttackSpeedIncrease(float s);
    void SetPercentAttackSpeedIncrease(float s);
    void SetFlatHealthIncrease(float h);
    void SetPercentHealthIncrease(float h );
    void SetFlatAuraDamageIncrease( float d);
    void SetPercentAuraDamageIncrease(float d);
    void SetFlatBulletCountIncrease(int d);
    void SetFlatProjectileSpeedIncrease(float ps);
    void SetPercentProjectileSpeedIncrease(float ps);

    float getDamage() { return ((baseDamage + flatDamageIncrease) + (1.0f * percentDamageIncrease)); }
    float getMaxHealth(){ return ((baseHealth + flatHealthIncrease) * (1.0f + percentHealthIncrease)); }
    float getSpeed(){ return ((baseSpeed + flatSpeedIncrease) * (1.0f + percentSpeedIncrease)); }
    float getAuraDamage(){ return ((baseAuraDamage + flatAuraDamageIncrease) * (1.0f + percentAuraDamageIncrease)); }
    float getAttackSpeed() { return ((baseAttackSpeed + flatAttackSpeedIncrease) * (1.0f + percentAttackSpeedIncrease)); }
    float getProjectileCount() { return (baseProjectileCount + flatProjectileCountIncrease); }
    float getProjectileSpeed() { return ((baseProjectileSpeed + flatProjectileSpeedIncrease) * (1.0f + percentProjectileSpeedIncrease)); }
};

#endif //__L4RC_GAME_ENTITY_H__