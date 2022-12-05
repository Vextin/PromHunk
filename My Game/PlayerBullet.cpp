/// \file PlayerBullet.cpp
/// \brief Code for the bullet object class CPlayerBullet.

#include "PlayerBullet.h"
#include "ComponentIncludes.h"
#include "Player.h"
#include "Enemy.h"

/// Create and initialize a player bullet object given its initial position.
/// \param t Sprite type of bullet.
/// \param p Initial position of bullet.

CPlayerBullet::CPlayerBullet(eSprite t, const Vector2& p, float damage) : CBullet(t, p) {
    m_damage = damage;
} //constructor


/// Response to collision, which for a bullet means playing a sound and a
/// particle effect, and then dying. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to nullptr).

void CPlayerBullet::CollisionResponse(const Vector2& norm, float d, CObject* pObj) 
{
    //bullets do not die if they hit other bullets or the player
    if (dynamic_cast<CBullet*>(pObj) != nullptr  ||  dynamic_cast<CPlayer*>(pObj) != nullptr) {
        return;
    }

    if (pObj == nullptr) { //collide with edge of world
        m_pAudio->SetScale(75.0f);
        m_pAudio->play(eSound::Ricochet, m_vPos, 1.0f);
    }
    else {
        m_pAudio->play(eSound::Clang, m_vPos, 1.0f);
    }

    CEnemy* enemy = dynamic_cast<CEnemy*>(pObj);
    if (enemy != nullptr)
    {
        if (enemy->TakeDamage(m_damage))
        {
            CObjectManager::totalEnemiesKilled++;
            CObjectManager::enemiesKilled++;
            if (CObjectManager::enemiesKilled >= CObjectManager::nextShopEnemyCount) {
                CObjectManager::enemiesKilled = 0;
                CObjectManager::nextShopEnemyCount *= 1.3f;
                m_pShop->ShowShopScreen();
            }
        }
    }
    //m_pAudio->SetListenerPos();

  //bullets die on collision
    if (!m_bDead) {
        m_bDead = true; //mark object for deletion
        DeathFX();
    } //if
} //CollisionResponse
