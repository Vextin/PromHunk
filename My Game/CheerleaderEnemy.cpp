/// \file BasicShooterEnemy.cpp
/// \brief Code for the BasicShooterEnemy object class CCheerleaderEnemy.

#include <list>

#include "CheerleaderEnemy.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Helpers.h"

/// Create and initialize a CheerleaderEnemy object given its position.
/// \param p Position of CheerleaderEnemy.

CCheerleaderEnemy::CCheerleaderEnemy(const Vector2& p) : CEnemy(eSprite::CheerleaderEnemy, p) {
    weapon = new CRangedWeapon(this, &CObjectManager::FireGun);//default enemy weaponm
    baseHealth = 1;
    health = baseHealth;
} //constructor

CCheerleaderEnemy::~CCheerleaderEnemy() {
    delete weapon;
}

/// Rotate the CheerleaderEnemy and fire the gun at at the closest available target if
/// there is one, and rotate the BasicShooterEnemy at a constant speed otherwise.

void CCheerleaderEnemy::move() {
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
} //move

/// Rotate the turrent towards a target point and file the gun if it is facing
/// sufficiently close to it.
/// \param pos Target point.

void CCheerleaderEnemy::RotateTowardsAndShootInRange(const Vector2& pos) {
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

void CCheerleaderEnemy::RotateTowardsAndMove(const Vector2& pos) {
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

void CCheerleaderEnemy::CheerBuff(std::list<CObject*> m_stdObjectList) { //do something to allies (enemies to player) in aoe
    
    BuffCooldown -= m_pTimer->GetFrameTime();
    
    if (BuffCooldown <= 0) {
        for (auto const& p : m_stdObjectList) { 
            if (dynamic_cast<CEntity*>(p) != nullptr) { //every enemy in ObjectList

                const Vector2 vDiff = m_vPos - p->m_vPos; //vector from Cheerleader to Enemy
                const float dSq = vDiff.LengthSquared(); //distance to cheerleader squared
                const float dMin = 75.0f; //max distance to buff
                const float dMinSq = dMin * dMin; //that distance squared


                if (dSq < dMinSq) //cheerleader is close enough to enemy to buff
                    dynamic_cast<CEntity*>(p)->health += 5; //buff that enemy
            } //if
        } //for
        BuffCooldown = 10.0f;
    } //if
}

