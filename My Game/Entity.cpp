/// \file Entity.cpp
#include "Entity.h"

CEntity::CEntity(eSprite t, const Vector2& p) : CObject(t, p) {
	if (t == eSprite::Dummy)
		health = INT32_MAX;
} //constructor

bool CEntity::TakeDamage(int d)
{
	const char* str = std::string(std::to_string(d)).append(" damage!").c_str();

	m_pRenderer->DrawCenteredText(str, Colors::Black);
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