/// \file Obstacle.cpp
#include "Obstacle.h"
#include "Bullet.h"
#include "FootballerEnemy.h"
#include "ComponentIncludes.h"

CObstacle::CObstacle(eSprite t, const Vector2& p) : CEntity(t, p) {
	health = baseHealth;
	m_bStatic = true;
} //constructor

bool CObstacle::TakeDamage(float d)
{
	health -= d;
	if (health <= 0)
	{
		Die();
		return true;
	}
	return false;
}

void CObstacle::Update() {

}

void CObstacle::Die()
{
	m_bDead = true;
}

void CObstacle::CollisionResponse(const Vector2& norm, float d, CObject* pObj) { ///< Collision response.
	CObject::CollisionResponse(norm, d, pObj);

	auto bullet = dynamic_cast<CPlayer*>(pObj);
	if (dynamic_cast<CBullet*>(pObj)) {
		TakeDamage(getDamage());
		m_pAudio->play(eSound::Ricochet);
	}
}