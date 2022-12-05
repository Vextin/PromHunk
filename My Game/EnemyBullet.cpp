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

    if (pObj == nullptr) //collide with edge of world
    m_pAudio->SetScale(75.0f);
    m_pAudio->play(eSound::Ricochet, m_vPos, 1.0f);

    //CEntity* ent = dynamic_cast<CEntity*>(pObj);
    //if (ent != nullptr)
    //{
    //    CPlayer* player = dynamic_cast<CPlayer*>(pObj);
    //    if (player != nullptr) {
    //        if (ent->TakeDamage(m_damage))
    //        {
    //            //hit player
    //        }
    //    }
    //}

    // If object is an entity, but not an enemy, apply damage
    if (dynamic_cast<CEntity*>(pObj) != nullptr && dynamic_cast<CEnemy*>(pObj) == nullptr)
        dynamic_cast<CEntity*>(pObj)->TakeDamage(m_damage);

    // If object is a player, don't damage
    if (dynamic_cast<CEnemy*>(pObj) != nullptr)
        return;

    //m_pAudio->SetListenerPos();
    //bullets do not die if they hit other bullets
    if (dynamic_cast<CBullet*>(pObj) != nullptr) {
        return;
    }

    //bullets die on collision
    if (!m_bDead) {
        m_bDead = true; //mark object for deletion
        DeathFX();
    } //if
} //CollisionResponse