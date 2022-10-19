/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "Helpers.h"

/// Create and initialize an player object given its initial position.
/// \param p Initial position of player.
CPlayer::CPlayer(const Vector2& p): CEntity(eSprite::Player, p){ 
  m_bIsTarget = true;
  m_bStatic = false;
  moveVector = new Vector2(0, 0);
  //weapon = new CRangedWeapon(this, &CObjectManager::PlayerDefaultWeapon);//default player weapon
  weapon = new CRangedWeapon(this, &CObjectManager::PlayerTestShotgun);
} //constructor

CPlayer::~CPlayer() {
    delete weapon;
}

/// Move and rotate in response to device input. The amount of motion and
/// rotation speed is proportional to the frame time.

void CPlayer::move(){
  const float t = m_pTimer->GetFrameTime(); //time
  const Vector2 view = GetViewVector(); //view vector
  m_vPos.x += moveVector->x * t * maxMoveSpeed;
  m_vPos.y += moveVector->y * t * maxMoveSpeed;
} //move

/// Response to collision. If the object being collided with is a bullet, then
/// play a sound, otherwise call `CObject::CollisionResponse` for the default
/// collision response.
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void CPlayer::CollisionResponse(const Vector2& norm, float d, CObject* pObj){
  if(pObj && pObj->isBullet())
    m_pAudio->play(eSound::Grunt);

  else CObject::CollisionResponse(norm, d, pObj);
} //CollisionResponse



void CPlayer::ProcessInput()
{
    //Set movement vector
    moveVector->x = 0;
    moveVector->y = 0;
    if (m_pKeyboard->Down('W')) moveVector->y += 1;
    if (m_pKeyboard->Down('A')) moveVector->x -= 1;
    if (m_pKeyboard->Down('S')) moveVector->y -= 1;
    if (m_pKeyboard->Down('D')) moveVector->x += 1;

    //Set sprite rotation
    if (moveVector->Length() > .01f) {
        m_fRoll = atan2(moveVector->y, moveVector->x);
    }

    //Fire weapon
    if (m_pKeyboard->Down(VK_SPACE)) {
        weapon->FireWeapon();
    }
}//ProcessInput

/// Reader function for position.
/// \return Position
const Vector2& CPlayer::GetPos() const{
  return m_vPos;
} //GetPos
