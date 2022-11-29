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
  baseHealth = FLT_MAX;
  moveVector = new Vector2(0, 0);
  baseProjectileCount = 4;
  baseProjectileSpeed = 1000.0f;
  baseAttackSpeed = 4.0f;
  health = baseHealth;
  weapon = new CRangedWeapon(this, &CObjectManager::PlayerDefaultWeapon);//default player weapon
  //weapon = new CRangedWeapon(this, &CObjectManager::PlayerTestShotgun);
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

void CPlayer::Update() {
    weapon->ReduceCooldown(m_pTimer->GetFrameTime());
}

void CPlayer::ProcessInput()
{
    if (dynamic_cast<CPlayer*>(m_pPlayer) == nullptr) return;
    //TODO - add controller support
    //Set movement vector
    moveVector->x = 0;
    moveVector->y = 0;
    if (m_pKeyboard->Down('W')) moveVector->y += 1;
    if (m_pKeyboard->Down('A')) moveVector->x -= 1;
    if (m_pKeyboard->Down('S')) moveVector->y -= 1;
    if (m_pKeyboard->Down('D')) moveVector->x += 1;

    //Set aim direction (sprite rotation)
    Vector2 aimVector = Vector2::Zero;

    m_pMouse->GetState(); //Update mouse state   
    if (m_pMouse->TriggerDown(eMouseButton::Left)) { //only use mouse aim if using left click to fire
        //mouse pos origin top left
        Vector2 camPos = m_pRenderer->GetCameraPos(); //cam center pos in world space
        Vector2 bottomLeftOfScreen = camPos - Vector2(m_nWinWidth/2, m_nWinHeight/2); //bottom left corner of screen in world space
        Vector2 playerDistFromBottomLeft = m_vPos - bottomLeftOfScreen; //essentially player position in screen space, origin at bottom left
        Vector2 flippedMousePos = Vector2(m_pMouse->Position.x, m_nWinHeight - m_pMouse->Position.y); //mouse pos in screen space with origin at bottom left

        aimVector = flippedMousePos - playerDistFromBottomLeft;
    }

    //otherwise if pressing arrow keys, aim with those
    if (m_pKeyboard->Down(38)) aimVector.y += 1; //up
    if (m_pKeyboard->Down(40)) aimVector.y -= 1; //down
    if (m_pKeyboard->Down(37)) aimVector.x -= 1; //left
    if (m_pKeyboard->Down(39)) aimVector.x += 1; //right
    if (aimVector != Vector2::Zero) {
        m_fRoll = static_cast<float>(atan2(aimVector.y, aimVector.x));
    }
    //otherwise, use the movement direction as aim direction
    else if (moveVector->Length() > .01f) {
        m_fRoll = static_cast<float>(atan2(moveVector->y, moveVector->x));
    }

    //Fire weapon
    if (m_pKeyboard->Down(VK_SPACE)) {
        weapon->FireWeapon();
    }
    if (m_pMouse->TriggerDown(eMouseButton::Left)) {
        weapon->FireWeapon();
    }
}//ProcessInput

/// Reader function for position.
/// \return Position
const Vector2& CPlayer::GetPos() const{
  return m_vPos;
} //GetPos
