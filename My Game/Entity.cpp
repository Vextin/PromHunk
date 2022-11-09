/// \file Entity.cpp
#include "Entity.h"

CEntity::CEntity(eSprite t, const Vector2& p) : CObject(t, p) {
} //constructor

bool CEntity::TakeDamage(int d)
{
	health -= d;
	if (health <= 0)
	{
		Die();
		return true;
	}
	return false;
}

void CEntity::Die()
{
	m_bDead = true;
}