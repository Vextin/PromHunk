/// \file RangedWeapon.h
#ifndef __L4RC_GAME_RANGED_WEAPON_H__
#define __L4RC_GAME_RANGED_WEAPON_H__

#include "ObjectManager.h"
#include "Entity.h"

typedef void (CObjectManager::* WeaponFunction)(CObject*, eSprite); //pointer to bullet creation function

///Abstract class for Entities that use ranged weapons
class CRangedWeapon: public CCommon, public LComponent
{
protected:
	float weaponCooldown = 0;
	WeaponFunction fireWeapon; ///pointer to bullet creation function
	CEntity* owner;
public:
	CRangedWeapon(CEntity*, WeaponFunction);///Constructor
	void SetCooldown(float);
	void FireWeapon();
};

#endif //__L4RC_GAME_RANGED_WEAPON_H__