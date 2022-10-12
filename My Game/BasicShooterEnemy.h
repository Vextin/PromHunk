/// \file BasicShooterEnemy.h
/// \brief Interface for the BasicShooterEnemy object class CBasicShooterEnemy.

#ifndef __L4RC_GAME_BasicShooterEnemy_H__
#define __L4RC_GAME_BasicShooterEnemy_H__

#include "Object.h"

/// \brief The BasicShooterEnemy object. 
///
/// CBasicShooterEnemy is the abstract representation of a BasicShooterEnemy object.

class CBasicShooterEnemy: public CObject{
  protected:
    void RotateTowardsAndShootInRange(const Vector2&); ///< Swivel towards position.
    void RotateTowardsAndMove(const Vector2&);  ///< Move towards player
    virtual void CollisionResponse(const Vector2&, float,
      CObject* = nullptr); ///< Collision response.
  
  public:
    CBasicShooterEnemy(const Vector2& p); ///< Constructor.
    virtual void move(); ///< Move BasicShooterEnemy.
}; //CBullet

#endif //__L4RC_GAME_BasicShooterEnemy_H__