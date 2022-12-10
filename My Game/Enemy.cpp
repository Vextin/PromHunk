/// \file Entity.cpp
#include "Enemy.h"
#include "ComponentIncludes.h"
#include "Player.h"

CEnemy::CEnemy(eSprite t, const Vector2& p) : CEntity(t, p) {
	m_bStatic = false; //Enemies are not static
	health = baseHealth;
} //constructor

void CEnemy::draw()
{
	float temp = m_fRoll;
	m_fRoll = 0;
	__super::draw();
	m_fRoll = temp;

}
void CEnemy::move()
{
	Vector2* moveVector = new Vector2(m_pPlayer->m_vPos - m_vPos);
	FlipSpriteToFacing(&m_fRoll, moveVector, &m_nCurrentFrame);


	delete moveVector;
}

void CEnemy::CollisionResponse(const Vector2& norm, float d, CObject* pObj) { ///< Collision response.
	CObject::CollisionResponse(norm, d, pObj);

	auto player = dynamic_cast<CPlayer*>(pObj);
	if (player) {
		player->TakeDamage(getDamage());
		m_vPos += (m_vPos - player->m_vPos);
		m_pAudio->play(eSound::Grunt);
	}
}