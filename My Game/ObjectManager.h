/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"

/// \brief The object manager.
///
/// A collection of all of the game objects.

class CObjectManager :
    public LBaseObjectManager<CObject>,
    public CCommon
{
private:
    void BroadPhase(); ///< Broad phase collision detection and response.
    void NarrowPhase(CObject*, CObject*); ///< Narrow phase collision detection and response.
    bool AtWorldEdge(CObject*, Vector2&, float&) const; ///< Test whether at the edge of the world.

public:
    CObject* create(eSprite, const Vector2&); ///< Create new object.
    CObject* createBullet(eSprite, const Vector2&, float damage=1.f); ///< Create new object.
    void FireGun(CObject*, eSprite); ///Default enemy weapon
    void PlayerDefaultWeapon(CObject*, eSprite);///Default player weapon
    void PlayerTestShotgun(CObject*, eSprite);

    void CheckBuffs();
}; //CObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__