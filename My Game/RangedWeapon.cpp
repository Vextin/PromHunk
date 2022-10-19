#include "RangedWeapon.h"
#include "ComponentIncludes.h"
#include "Entity.h"

CRangedWeapon::CRangedWeapon(CEntity* owner, WeaponFunction wep) {
    this->owner = owner;
    fireWeapon = wep;
}

void CRangedWeapon::SetCooldown(float cooldown) {
    weaponCooldown = cooldown;
}//SetCooldown

void CRangedWeapon::FireWeapon() {
    weaponCooldown -= m_pTimer->GetFrameTime();
    if (weaponCooldown <= 0) {
        std::invoke(fireWeapon, m_pObjectManager, owner, eSprite::Bullet);
    }
}//FireWeapon