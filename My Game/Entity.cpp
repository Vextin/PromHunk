/// \file Entity.cpp
#include "Entity.h"

CEntity::CEntity(eSprite t, const Vector2& p) : CObject(t, p) {
	if (t == eSprite::Dummy)
		health = FLT_MAX;
} //constructor

bool CEntity::TakeDamage(float d)
{
	//const char* str = std::string(std::to_string(d)).append(" damage!").c_str();

	//m_pRenderer->DrawCenteredText(str, Colors::Black);
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
void CEntity::SetFlatDamageIncrease(float d)
{
	flatDamageIncrease += d;
}
void CEntity::SetPercentDamageIncrease(float d)
{
	percentDamageIncrease += d;
}
void CEntity::SetFlatSpeedIncrease(float s)
{
	flatSpeedIncrease += s;
}
void CEntity::SetPercentSpeedIncrease(float s)
{
	percentSpeedIncrease += s;
}
void CEntity::SetFlatAttackSpeedIncrease(float s)
{
	flatAttackSpeedIncrease += s;
}
void CEntity::SetPercentAttackSpeedIncrease(float s)
{
	percentAttackSpeedIncrease += s;
}
void CEntity::SetFlatHealthIncrease(float h)
{
	flatHealthIncrease += h;
}
void CEntity::SetPercentHealthIncrease(float h)
{
	percentHealthIncrease += h;
}
void CEntity::SetFlatAuraDamageIncrease(float d)
{
	flatAuraDamageIncrease += d;
}
void CEntity::SetPercentAuraDamageIncrease(float d)
{
	percentAuraDamageIncrease += d;
}
void CEntity::SetFlatBulletCountIncrease(int c)
{
	flatProjectileCountIncrease += c;
}
void CEntity::SetFlatProjectileSpeedIncrease(float ps)
{
	flatProjectileSpeedIncrease += ps;
}
void CEntity::SetPercentProjectileSpeedIncrease(float ps)
{
	percentProjectileSpeedIncrease += ps;
}