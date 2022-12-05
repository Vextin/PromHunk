/// \file PlayerBullet.h
/// \brief Interface for the bullet object class PlayerBullet

#ifndef __L4RC_GAME_PLAYERBULLET_H__
#define __L4RC_GAME_PLAYERBULLET_H__

#include "Bullet.h"
#include "Shop.h"
/// \brief The playerbullet object. 
///
/// The abstract representation of a playerbullet object. 

class CPlayerBullet : public CBullet
{
protected:
    void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.

public:
    CPlayerBullet(eSprite t, const Vector2& p, float damage = 1); ///< Constructor.
}; //CBullet

#endif //__L4RC_GAME_BULLET_H__