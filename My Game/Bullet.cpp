/// \file Bullet.cpp
/// \brief Code for the bullet object class CBullet.

#include "Bullet.h"
#include "ComponentIncludes.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"
#include "Player.h"
#include "Enemy.h"

/// Create and initialize a bullet object given its initial position.
/// \param t Sprite type of bullet.
/// \param p Initial position of bullet.

CBullet::CBullet(eSprite t, const Vector2& p, float damage): CObject(t, p){
    soundFalloff = 4.0f;
    m_damage = damage;
  m_bIsBullet = true;
  m_bStatic = false;
  m_bIsTarget = false;
} //constructor



/// Response to collision, which for a bullet means playing a sound and a
/// particle effect, and then dying. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to nullptr).

void CBullet::CollisionResponse(const Vector2& norm, float d, CObject* pObj){
} //CollisionResponse

/// Create a smoke particle effect to mark the death of the bullet.

void CBullet::DeathFX(){
  LParticleDesc2D d; //particle descriptor

  d.m_nSpriteIndex = (UINT)eSprite::Smoke;
  d.m_vPos = m_vPos;
  d.m_fLifeSpan = 0.5f;
  d.m_fMaxScale = 0.5f;
  d.m_fScaleInFrac = 0.2f;
  d.m_fFadeOutFrac = 0.8f;
  d.m_fScaleOutFrac = d.m_fFadeOutFrac;

  m_pParticleEngine->create(d); //create particle
} //DeathFX