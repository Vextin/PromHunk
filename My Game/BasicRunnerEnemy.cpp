/// \file BasicShooterEnemy.cpp
/// \brief Code for the BasicShooterEnemy object class CBasicRunnerEnemy.

#include "BasicRunnerEnemy.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Helpers.h"
#include "ObstacleManager.h"
#include <stack>

/// Create and initialize a BasicRunnerEnemy object given its position.
/// \param p Position of BasicRunnerEnemy.

CBasicRunnerEnemy::CBasicRunnerEnemy(const Vector2& p) : CEnemy(eSprite::BasicRunnerEnemy, p) {
    weapon = new CRangedWeapon(this, &CObjectManager::FireGun);//default enemy weapon
    baseHealth = 2;
    health = baseHealth;
    killxp = 1.5f;
} //constructor

CBasicRunnerEnemy::~CBasicRunnerEnemy() {
    delete weapon;
}

void CBasicRunnerEnemy::calcPath()
{
    Pair src = m_pObstacleManager->getxyPair(m_vPos); // location of self
    Pair dest = m_pObstacleManager->getxyPair(m_pPlayer->m_vPos); // location of player
    m_pObstacleManager->aStarSearch(src, dest); //a* search
    path2player = m_pObstacleManager->path2targ;
}

/// Rotate the BasicRunnerEnemy and fire the gun at at the closest available target if
/// there is one, and rotate the BasicShooterEnemy at a constant speed otherwise.

void CBasicRunnerEnemy::move() {
    if (isPaused) return;
    if (m_pPlayer) {
        const Vector2 vDiff = m_vPos - m_pPlayer->m_vPos; //vector from player to BasicShooterEnemy
        const float dSq = vDiff.LengthSquared(); //distance to player squared
        const float dMin = 5.0f; //minimum distance at which player is invisible
        const float dMinSq = dMin * dMin; //that squared

        if (dSq < 80.0f) //player within 80.0f dist
            RotateTowardsAndMove(m_pPlayer->m_vPos);
        else 
        {
            PathFindCooldown -= m_pTimer->GetFrameTime();
            if (path2player.empty() || PathFindCooldown <= 0)
            {
                calcPath();
                PathFindCooldown = 2.0f;
            }
            if (m_pObstacleManager->getxyPair(m_vPos) == path2player.top())
                path2player.pop();
            Vector2 nextpos = m_pObstacleManager->getVector(path2player.top());
            RotateTowardsAndMove(nextpos);
        }
    } //if

    m_fRoll += 0.2f * m_fRotSpeed * XM_2PI * m_pTimer->GetFrameTime(); //rotate
    NormalizeAngle(m_fRoll); //normalize to [-pi, pi] for accuracy
    

    __super::move();
    
} //move

/// Rotate the turrent towards a target point and file the gun if it is facing
/// sufficiently close to it.
/// \param pos Target point.

void CBasicRunnerEnemy::RotateTowardsAndShootInRange(const Vector2& pos) {
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

void CBasicRunnerEnemy::RotateTowardsAndMove(const Vector2& pos) {
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