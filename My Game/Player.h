/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Entity.h"
#include "RangedWeapon.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer: 
    public CEntity,
    public LSettings{
    protected:  
        //bool m_bStrafeLeft = false; ///< Strafe left.
        //bool m_bStrafeRight = false; ///< Strafe right.
        //bool m_bStrafeBack = false; ///< Strafe back.
        Vector2* moveVector;
        LSpriteDesc2D* crosshair;
        void CollisionResponse(const Vector2&, float, CObject* = nullptr) override; ///< Collision response.
        long currentlevel = 0;
        float currentxp = 0.0f;
        float maxxp = 5.0f;

    public:
        CRangedWeapon* weapon;

        CPlayer(const Vector2& p); ///< Constructor.
        ~CPlayer();//Deconstructor

        void ProcessInput(); ///Player input
        void move() override; ///< Move player object.
        const Vector2& GetPos() const; ///< Get position.
        void Update() override;

        void draw() override;
        void Die() override;

        void addxp(float xp);

        float getcurrentxp() { return currentxp; };
        float getmaxxp() { return maxxp; };
        void levelup();

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__