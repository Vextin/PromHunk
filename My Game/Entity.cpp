/// \file Entity.cpp
#include "Entity.h"

CEntity::CEntity(eSprite t, const Vector2& p) : CObject(t, p) {
	if (t == eSprite::Dummy)
		health = baseHealth;
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

void CEntity::Update() {

}

void CEntity::FlipSpriteToFacing(float* roll, Vector2* moveVector, UINT* currentFrame)
{
	

    //the dot product of the move vector and the unit X vector returns a scalar value
    //that is positive if the player is moving to the right, and negative if the 
    //player is moving to the left. Math!
    //there's a little bit of wiggle room so that moving almost exactly down with a 
    //gamepad doesn't cause jitter. Anticipating the bug, not even sure if it would happen.
    if (moveVector->Dot(Vector2::UnitX) >= 0.1f)
    {
        *currentFrame = 0;
    }
    if (moveVector->Dot(Vector2::UnitX) <= -0.1f)
    {
        *currentFrame = 1;
    }
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
	float healthBefore = getMaxHealth();
	flatHealthIncrease += h;
	float healthAfter = getMaxHealth();
	health += healthAfter - healthBefore;
}
void CEntity::SetPercentHealthIncrease(float h)
{
	float healthBefore = getMaxHealth();
	percentHealthIncrease += h;
	float healthAfter = getMaxHealth();
	health += healthAfter - healthBefore;
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