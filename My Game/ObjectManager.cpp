/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"

#include "Player.h"
#include "BasicShooterEnemy.h"
#include "BasicRunnerEnemy.h"
#include "CheerleaderEnemy.h"
#include "Bullet.h"
#include "ParticleEngine.h"
#include "Helpers.h"
#include "GameDefines.h"

/// Create an object and put a pointer to it at the back of the object list
/// `m_stdObjectList`, which it inherits from `LBaseObjectManager`.
/// \param t Sprite type.
/// \param pos Initial position.
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSprite t, const Vector2& pos){
    CObject* pObj = nullptr;

    switch(t){ //create object of type t
        case eSprite::Player:  pObj = new CPlayer(pos); break;

        case eSprite::Dummy:    pObj = new CEntity(eSprite::Dummy, pos); break;
        case eSprite::BasicShooterEnemy:  pObj = new CBasicShooterEnemy(pos); break;
        case eSprite::BasicRunnerEnemy: pObj = new CBasicRunnerEnemy(pos); break;
        case eSprite::CheerleaderEnemy: pObj = new CCheerleaderEnemy(pos); break;

        case eSprite::Bullet:  pObj = new CBullet(eSprite::Bullet,  pos); break;
        case eSprite::Bullet2: pObj = new CBullet(eSprite::Bullet2, pos); break;
        default: pObj = new CObject(t, pos);
    } //switch
  
    m_stdObjectList.push_back(pObj); //push pointer onto object list
    return pObj; //return pointer to created object
} //create

CObject* CObjectManager::createBullet(eSprite t, const Vector2& pos, float damage) {
    CObject* pObj = nullptr;

    switch (t) { //create object of type t
    case eSprite::Bullet:  pObj = new CBullet(eSprite::Bullet, pos, damage); break;

    } //switch

    m_stdObjectList.push_back(pObj); //push pointer onto object list
    return pObj; //return pointer to created object
} //create

/// Test whether an object's left, right, top or bottom edge has crossed the 
/// left, right, top, bottom edge of the world, respectively. If so, then the
/// object's position is corrected. This function assumes that the bottom left
/// corner of the world is at the origin.
/// \param p Pointer to an object.
/// \param norm [out] Collision normal.
/// \param d [out] Overlap distance.
/// \return true if the object overlaps the edge of the world.

bool CObjectManager::AtWorldEdge(CObject* p, Vector2& norm, float& d) const{ 
    d = 0; //safety

    float w, h; //for sprite width and height
    m_pRenderer->GetSize(p->m_nSpriteIndex, w, h); //get sprite width and height
    w *= p->m_fXScale/2; //scaled half width
    h *= p->m_fYScale/2; //scale half height
        
    if(p->m_vPos.x < w){ //left edge
        norm = Vector2::UnitX;
        d = w - p->m_vPos.x;
    } //if

    else if(p->m_vPos.x > m_vWorldSize.x - w){ //right edge
        norm = -Vector2::UnitX;
        d = p->m_vPos.x - m_vWorldSize.x + w;
    } //else if

    else if(p->m_vPos.y < h){ //bottom edge
        norm = Vector2::UnitY;
        d = h - p->m_vPos.y;
    } //else if

    else if(p->m_vPos.y > m_vWorldSize.y - h){ //top edge
        norm = -Vector2::UnitY;
        d = p->m_vPos.y - m_vWorldSize.y + h;
    } //else if

  return d > 0;
} //AtWorldEdge

/// Perform collision detection and response for each object with the world
/// edges and for all objects with another object, making sure that each pair
/// of objects is processed only once.

void CObjectManager::CheckBuffs() {
    for (auto const& p : m_stdObjectList) //for each object
        if (dynamic_cast<CCheerleaderEnemy*>(p) != nullptr)
        {
            dynamic_cast<CCheerleaderEnemy*>(p)->CheerBuff(m_stdObjectList); //buff
        }
}

void CObjectManager::BroadPhase(){
    LBaseObjectManager::BroadPhase(); //collide with other objects

    //collide with walls

    for(CObject* pObj: m_stdObjectList) //for each object
    if(!pObj->m_bDead){ //for each non-dead object, that is
        for(int i=0; i<2; i++){ //can collide with 2 edges simultaneously
        Vector2 norm; //collision normal
        float d = 0; //overlap distance

        if(AtWorldEdge(pObj, norm, d)) //collide with world edge
            pObj->CollisionResponse(norm, d); //respond 
        } //for
    } //for
} //BroadPhase

/// Perform collision detection and response for a pair of objects. Makes
/// use of the helper function Identify() because this function may be called
/// with the objects in an arbitrary order.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1){
    Vector2 vSep = p0->m_vPos - p1->m_vPos; //vector from *p1 to *p0
    const float d = p0->m_fRadius + p1->m_fRadius - vSep.Length(); //overlap

    if(d > 0.0f){ //bounding circles overlap
    vSep.Normalize(); //vSep is now the collision normal

    p0->CollisionResponse( vSep, d, p1); //this changes separation of objects
    p1->CollisionResponse(-vSep, d, p0); //same separation and opposite normal
    } //if
} //NarrowPhase

/// Create a bullet object and a flash particle effect. It is assumed that the
/// object is round and that the bullet appears at the edge of the object in
/// the direction that it is facing and continues moving in that direction.
/// \param pObj Pointer to an object.
/// \param bullet Sprite type of bullet.

void CObjectManager::FireGun(CObject* pObj, eSprite bullet){
    CBasicShooterEnemy* enemy = dynamic_cast<CBasicShooterEnemy*>(pObj);
    if (enemy) {
        enemy->weapon->SetCooldown(0);
    }

    m_pAudio->play(eSound::Gun);

    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    const float w0 = 0.5f*m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
    const Vector2 pos = pObj->m_vPos + (w0 + w1)*view; //bullet initial position

    //create bullet object

    CObject* pBullet = createBullet(bullet, pos, enemy->getDamage()); //create bullet

    const Vector2 norm = VectorNormalCC(view); //normal to view direction
    const float m = 2.0f*m_pRandom->randf() - 1.0f; //random deflection magnitude
    const Vector2 deflection = 0.01f*m*norm; //random deflection

    pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f*(view + deflection);
    pBullet->m_fRoll = pObj->m_fRoll; 

    //particle effect for gun fire
  
    LParticleDesc2D d;

    d.m_nSpriteIndex = (UINT)eSprite::Spark;
    d.m_vPos = pos;
    d.m_vVel = pObj->m_fSpeed*view;
    d.m_fLifeSpan = 0.25f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_fMaxScale = 0.5f;
    d.m_f4Tint = XMFLOAT4(Colors::Yellow);
  
    m_pParticleEngine->create(d);
} //FireGun


void CObjectManager::PlayerDefaultWeapon(CObject* pObj, eSprite bullet) {
    CPlayer* player = dynamic_cast<CPlayer*>(pObj);
    if (!player) {
        return; //this function should never be called with anything other than the player
    }

    player->weapon->SetCooldown(1.0f / player->getAttackSpeed()); //set time until player can fire again (inverse of speed)

    m_pAudio->play(eSound::Gun);

    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    const float w0 = 0.5f * m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
    const Vector2 pos = pObj->m_vPos + (w0 + w1) * view; //firing position
    const Vector2 norm = VectorNormalCC(view); //normal to view direction

    //create bullet object
    int bulletCount = player->getProjectileCount(); //number of bullets to fire
    float spread = M_PI / 18.0f; //angle between bullets 10 degrees TODO - eventually should be dynamic based on bullet count
    float minAngle = -((bulletCount-1) * spread) / 2.0f; //angle of first bullet
    for (int i = 0; i < bulletCount; i++)
    {
        CObject* pBullet = createBullet(bullet, pos, m_pPlayer->getDamage()); //create bullet

        float m = 2.0f * m_pRandom->randf() - 1.0f; //random deflection magnitude
        Vector2 deflection = 0.01f * m * norm; //random deflection
        Vector2 finalAngle = Vector2::TransformNormal(view, Matrix::CreateRotationZ(minAngle + i * spread)) + deflection;
        pBullet->m_vVelocity = pObj->m_vVelocity + player->getProjectileSpeed() * finalAngle;
        pBullet->m_fRoll = pObj->m_fRoll;
    }

    //particle effect for gun fire
    LParticleDesc2D d;

    d.m_nSpriteIndex = (UINT)eSprite::Spark;
    d.m_vPos = pos;
    d.m_vVel = pObj->m_vVelocity + (player->getProjectileSpeed() / 10.0f) * view; //particles inherit some of bullet speed
    d.m_fLifeSpan = 0.25f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_fMaxScale = 0.5f;
    d.m_f4Tint = XMFLOAT4(Colors::Yellow);

    m_pParticleEngine->create(d);
} //FireGun

void CObjectManager::PlayerTestShotgun(CObject* pObj, eSprite bullet) {
    CPlayer* player = dynamic_cast<CPlayer*>(pObj);
    if (player) {
        player->weapon->SetCooldown(0.5f);
    }

    m_pAudio->play(eSound::Gun);

    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    const float w0 = 0.5f * m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
    const Vector2 pos = pObj->m_vPos + (w0 + w1) * view; //firing position
    const Vector2 norm = VectorNormalCC(view); //normal to view direction

    //create bullet object
    for (int i = -1; i <= 1; i++) {

        Vector2 bulletPos = pos + (norm * 5.0f * i);
        CObject* pBullet = createBullet(bullet, bulletPos, m_pPlayer->getDamage()); //create bullet

        const float m = 2.0f * m_pRandom->randf() - 1.0f; //random deflection magnitude
        const Vector2 deflection = 0.01f * m * norm; //random deflection
        Vector2 bulletAngle = i*norm; //TODO - this is dumb rewrite this
        Vector2 finalAngle = view + deflection + bulletAngle;
        finalAngle.Normalize();
        pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f * finalAngle;
        pBullet->m_fRoll = pObj->m_fRoll;
    }

    //particle effect for gun fire
    LParticleDesc2D d;

    d.m_nSpriteIndex = (UINT)eSprite::Spark;
    d.m_vPos = pos;
    d.m_vVel = pObj->m_fSpeed * view;
    d.m_fLifeSpan = 0.25f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_fMaxScale = 0.5f;
    d.m_f4Tint = XMFLOAT4(Colors::Yellow);

    m_pParticleEngine->create(d);
} //FireGun
