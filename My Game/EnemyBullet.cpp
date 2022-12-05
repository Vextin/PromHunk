#include "EnemyBullet.h"
#include "ComponentIncludes.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"
#include "Player.h"
#include "Enemy.h"

CEnemyBullet::CEnemyBullet(eSprite t, const Vector2& p, float damage) : CBullet(t, p) {
    m_damage = damage;
} //constructor


void CEnemyBullet::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
    //bullets do not die if they hit other bullets
    if (dynamic_cast<CBullet*>(pObj) != nullptr) {
        return;
    }
    //bullets do not die if they hit other enemies
    if (dynamic_cast<CEnemy*>(pObj) != nullptr) {
        return;
    }

    if (pObj == nullptr) { //collide with edge of world
        m_pAudio->SetScale(75.0f);
        m_pAudio->play(eSound::Ricochet, m_vPos, 1.0f);
    }

    // If object is player apply damage
    auto player = dynamic_cast<CPlayer*>(pObj);
    if (player != nullptr) {
        m_pAudio->play(eSound::Grunt);
        if (player->TakeDamage(m_damage)) {
            //game over
        }
    }

    //bullets die on collision
    if (!m_bDead) {
        m_bDead = true; //mark object for deletion
        DeathFX();
    } //if
} //CollisionResponse