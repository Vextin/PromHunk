/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Object.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer: public CObject{
  protected:  
    bool m_bStrafeLeft = false; ///< Strafe left.
    bool m_bStrafeRight = false; ///< Strafe right.
    bool m_bStrafeBack = false; ///< Strafe back.
    float maxMoveSpeed = 100;
    Vector2* moveVector;
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

  public:
    CPlayer(const Vector2& p); ///< Constructor.

    void CalculateMovement();
    virtual void move(); ///< Move player object.


    //REMOVED FUNCTIONS: ~Austin Carlin
    //void SetSpeed(const float speed); ///< Set speed.
    //void SetRotSpeed(const float speed); ///< Set rotational velocity.
    
    //void StrafeLeft(); ///< Strafe left.
    //void StrafeRight(); ///< Strafe right.
    //void StrafeBack(); ///< Strafe back.
    
    const Vector2& GetPos() const; ///< Get position.
}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__