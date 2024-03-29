/// \file FootballerEnemy.cpp
/// \brief Code for the FootballerEnemy object class CFootballerEnemy.

#include <list>

#include "FootballerEnemy.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Helpers.h"
#include "Obstacle.h"

/// Create and initialize a FootballerEnemy object given its position.
/// \param p Position of FootballerEnemy.

CFootballerEnemy::CFootballerEnemy(const Vector2& p) : CEnemy(eSprite::FootballerEnemy, p) {
    weapon = new CRangedWeapon(this, &CObjectManager::FireGun);//default enemy weaponm
    baseHealth = 3;
    health = baseHealth;
    killxp = 3.0f;
} //constructor

CFootballerEnemy::~CFootballerEnemy() {
    delete weapon;
}

/// Rotate the FootballerEnemy and fire the gun at at the closest available target if
/// there is one, and rotate the BasicShooterEnemy at a constant speed otherwise.

void CFootballerEnemy::move() {
    if (isPaused) return;
    if (m_pPlayer) {
        const Vector2 vDiff = m_vPos - m_pPlayer->m_vPos; //vector from player to BasicShooterEnemy
        const float dSq = vDiff.LengthSquared(); //distance to player squared
        const float dMin = 5.0f; //minimum distance at which player is invisible
        const float dMinSq = dMin * dMin; //that squared


        if (dSq < dMinSq) //player is close enough to BasicShooterEnemy
            RotateTowardsAndShootInRange(m_pPlayer->m_vPos);
        else {
            //move untill in range
            RotateTowardsAndMove(m_pPlayer->m_vPos);
        }
    } //if

    m_fRoll += 0.2f * m_fRotSpeed * XM_2PI * m_pTimer->GetFrameTime(); //rotate
    NormalizeAngle(m_fRoll); //normalize to [-pi, pi] for accuracy
    __super::move();
} //move

/// Rotate the turrent towards a target point and file the gun if it is facing
/// sufficiently close to it.
/// \param pos Target point.

void CFootballerEnemy::RotateTowardsAndShootInRange(const Vector2& pos) {
    if (isPaused) return;
    const Vector2 v = pos - m_vPos; //vector from target to BasicShooterEnemy
    const float theta = atan2f(v.y, v.x); //orientation of that vector
    float diff = m_fRoll - theta; //difference with BasicShooterEnemy orientation
    NormalizeAngle(diff); //normalize to [-pi, pi]

    //set rotation speed from diff

    const float fAngleDelta = 0.05f; //allowable angle discrepancy
    const float fTrackingSpeed = 2.0f; //rotation speed when tracking

    if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
    else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwise
    else m_fRotSpeed = 0; //stop rotating

    //fire gun if pointing approximately towards target
    if (fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered()) {
        weapon->FireWeapon();
    }
} //RotateTowards

void CFootballerEnemy::RotateTowardsAndMove(const Vector2& pos) {
    if (isPaused) return;
    const Vector2 v = pos - m_vPos; //vector from target to BasicShooterEnemy
    const float theta = atan2f(v.y, v.x); //orientation of that vector
    const float t = m_pTimer->GetFrameTime(); //time
    const float speed = 50;
    const Vector2 view = GetViewVector(); //view vector
    float diff = m_fRoll - theta; //difference with BasicShooterEnemy orientation
    NormalizeAngle(diff); //normalize to [-pi, pi]

    //set rotation speed from diff

    const float fAngleDelta = 0.05f; //allowable angle discrepancy
    const float fTrackingSpeed = 2.0f; //rotation speed when tracking

    if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
    else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwise
    else m_fRotSpeed = 0; //stop rotating

    //move towards:
    if (fabsf(diff) < fAngleDelta) {
        //move to player
        m_vPos += speed * t * view;
    }
}

void CFootballerEnemy::Sprint() {

    if (isPaused) return;

    SprintCooldown -= m_pTimer->GetFrameTime();

    if (SprintCooldown <= 0) {
        SprintCooldown = 10.0f;
        speed += 10;
    }
}

void CFootballerEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) { ///< Collision response.
    CObject::CollisionResponse(norm, d, pObj);

    auto player = dynamic_cast<CPlayer*>(pObj);
    if (player) {
        player->TakeDamage(getDamage());
        m_vPos += (m_vPos - player->m_vPos);
        m_pAudio->play(eSound::Grunt);
    }
    auto obstacle = dynamic_cast<CObstacle*>(pObj);
    if (obstacle) {
        obstacle->TakeDamage(5.0f);
        m_vPos += (m_vPos - obstacle->m_vPos);
        m_pAudio->play(eSound::Grunt);
    }

}