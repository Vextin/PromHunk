/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "Shop.h"
#include "shellapi.h"
#include "Mouse.h"

/// Delete the particle engine and the object manager. The renderer needs to
/// be deleted before this destructor runs so it will be done elsewhere.

CGame::~CGame(){
  delete m_pParticleEngine;
  delete m_pObjectManager;
} //destructor

/// Create the renderer, the object manager, and the particle engine, load
/// images and sounds, and begin the game.

void CGame::Initialize(){
  m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D); 
  m_pRenderer->Initialize(eSprite::Size); 
  LoadImages(); //load images from xml file list

  m_pObjectManager = new CObjectManager; //set up the object manager 
  LoadSounds(); //load the sounds for this game

  m_pParticleEngine = new LParticleEngine2D(m_pRenderer);

  Shop::LoadJSON();
  m_pShop = new Shop;
  m_pMouse = new CMouse;
  m_pMouse->Initialize();
  BeginGame();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();

  m_pRenderer->Load(eSprite::Background, "floor");
  m_pRenderer->Load(eSprite::Player,  "player");
  m_pRenderer->Load(eSprite::Bullet,  "bullet");
  m_pRenderer->Load(eSprite::Bullet2, "bullet2");
  m_pRenderer->Load(eSprite::Smoke,   "smoke");
  m_pRenderer->Load(eSprite::Spark,   "spark");
  m_pRenderer->Load(eSprite::BasicShooterEnemy,  "turret");
  m_pRenderer->Load(eSprite::BasicRunnerEnemy, "runman");
  m_pRenderer->Load(eSprite::CheerleaderEnemy, "cheerleader");
  m_pRenderer->Load(eSprite::Dummy, "dummy");
  m_pRenderer->Load(eSprite::ShopCard_Damage1, "ShopCard_Damage_1");
  m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.
void CGame::LoadSounds(){
  m_pAudio->Initialize(eSound::Size);

  m_pAudio->Load(eSound::Grunt, "grunt");
  m_pAudio->Load(eSound::Clang, "clang");
  m_pAudio->Load(eSound::Gun, "gun");
  m_pAudio->Load(eSound::Ricochet, "ricochet");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object and a BasicShooterEnemy object.

void CGame::CreateObjects(){
  m_pRenderer->GetSize(eSprite::Background, m_vWorldSize.x, m_vWorldSize.y); //init m_vWorldSize

  m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::Player, Vector2(64.0f, 64.0f));

  
  
  m_pTargetDummy = (CEntity*)m_pObjectManager->create(eSprite::Dummy, Vector2(475.0f, 475.0f));
  m_pTargetDummy->m_fRoll = 0;

  
  m_pObjectManager->create(eSprite::BasicShooterEnemy, Vector2(430.0f, 430.0f));
  m_pObjectManager->create(eSprite::CheerleaderEnemy, Vector2(550.0f, 550.0f));
} //CreateObjects

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::SpawnEnemy(float x, float y) {
    m_pObjectManager->create(eSprite::BasicRunnerEnemy, Vector2(x, y));
}   //spawn enemy at a location

void CGame::SpawnCenterBox() {
    //TODO: max X and Y of a zone/map
    float max_X = 1000;
    float max_Y = 1000;

    SpawnEnemy(1.0, max_Y / 2);    //LEFT
    SpawnEnemy(max_X - 1.0, max_Y / 2);   //RIGHT
    
    SpawnEnemy(max_X / 2, max_Y);   //TOP
    SpawnEnemy(max_X / 2, 1.0);   //BOTTOM
}   //spawn one enemy at each corner

void CGame::SpawnNearPlayer() {
    float playerx = m_pPlayer->m_vPos.x;
    float playery = m_pPlayer->m_vPos.y;

    float randx = m_pRandom->randf() * 550.0f * RandomNegative();    //random distance needs to be pos/neg as well
    float randy = m_pRandom->randf() * 550.0f * RandomNegative();    //random distance needs to be pos/neg as well
    SpawnEnemy(playerx + randx, playery + randy);
}

float CGame::RandomNegative() {
    float randpos;
    if (m_pRandom->randf() < 0.5f) {
        randpos = -1.0f;
    }
    else {
        randpos = 1.0f;
    }
    return randpos;
}
void CGame::ShowShop()
{
    m_eGameState = eGameState::Shop;
    m_pShop->ShowShopScreen();
}

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles
  m_pObjectManager->clear(); //clear old objects
  CreateObjects(); //create new objects 
} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
  m_pKeyboard->GetState(); //get current keyboard state (only call once per frame or inputs will get cleared breaking TriggerDown())
  
  if(m_pKeyboard->TriggerDown(VK_F1)) //help
    ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);

  if(m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
    m_bDrawFrameRate = !m_bDrawFrameRate;

  if (m_pKeyboard->TriggerDown(VK_F3)) //toggle frame rate
      m_bDrawDamage = !m_bDrawDamage;

  if (m_pKeyboard->TriggerDown(VK_F4)) //toggle frame rate
      m_pShop->ShowShopScreen();

  if(m_pKeyboard->TriggerDown(VK_BACK)) //start game
    BeginGame();
  
  if (m_pKeyboard->TriggerDown('U')) //spawn enemy
      SpawnNearPlayer();

  if (m_pKeyboard->TriggerDown('I')) //spawn enemy
      SpawnCenterBox();

  if (m_eGameState == eGameState::Shop)
  {
      if (m_pKeyboard->TriggerDown('1'))
      {
          m_pShop->BuyItem(0);
          m_eGameState = eGameState::Playing;
      } else
      if (m_pKeyboard->TriggerDown('2'))
      {
          m_pShop->BuyItem(1);
          m_eGameState = eGameState::Playing;
      } else
      if (m_pKeyboard->TriggerDown('3'))
      {
          m_pShop->BuyItem(2);
          m_eGameState = eGameState::Playing;
      }
  }

  //ATTN: Movement code added to Player.cpp instead of Game.cpp ~Austin Carlin
  if (m_pPlayer && m_eGameState == eGameState::Playing) m_pPlayer->ProcessInput();
  
} //KeyboardHandler

/// Poll the XBox controller state and respond to the controls there.

//ATTN: Movement code added to Player.cpp instead of Game.cpp ~Austin Carlin
void CGame::ControllerHandler(){
    /*
  if(!m_pController->IsConnected())return;

  m_pController->GetState(); //get state of controller's controls 
  
  if(m_pPlayer){ //safety
    m_pPlayer->SetSpeed(100*m_pController->GetRTrigger());
    m_pPlayer->SetRotSpeed(-2.0f*m_pController->GetRThumb().x);

    if(m_pController->GetButtonRSToggle()) //fire gun
      m_pObjectManager->FireGun(m_pPlayer, eSprite::Bullet);

    if(m_pController->GetDPadRight()) //strafe right
      m_pPlayer->StrafeRight();
  
    if(m_pController->GetDPadLeft()) //strafe left
      m_pPlayer->StrafeLeft();

    if(m_pController->GetDPadDown()) //strafe back
      m_pPlayer->StrafeBack();
  } //if */
} //ControllerHandler


/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in `gamesettings.xml`.

void CGame::DrawFrameRateText(){
  const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
  const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
  m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

void CGame::DrawDamageText() {
    const std::string s = std::to_string(m_pPlayer->getDamage()) + " damage"; //frame rate
    const Vector2 pos(m_nWinWidth - 128.0f, 60.0f); //hard-coded position
    m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  m_pRenderer->Draw(eSprite::Background, m_vWorldSize/2.0f);  //draw background
  m_pObjectManager->draw(); //draw objects

  m_pParticleEngine->Draw(); //draw particles
  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if (m_bDrawDamage)DrawDamageText(); //draw frame rate, if required
  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

void CGame::FollowCamera(){
  if(m_pPlayer == nullptr)return; //safety
  Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

  if(m_vWorldSize.x > m_nWinWidth){ //world wider than screen
    vCameraPos.x = std::max(vCameraPos.x, m_nWinWidth/2.0f); //stay away from the left edge
    vCameraPos.x = std::min(vCameraPos.x, m_vWorldSize.x - m_nWinWidth/2.0f);  //stay away from the right edge
  } //if
  else vCameraPos.x = m_vWorldSize.x/2.0f; //center horizontally.
  
  if(m_vWorldSize.y > m_nWinHeight){ //world higher than screen
    vCameraPos.y = std::max(vCameraPos.y, m_nWinHeight/2.0f);  //stay away from the bottom edge
    vCameraPos.y = std::min(vCameraPos.y, m_vWorldSize.y - m_nWinHeight/2.0f); //stay away from the top edge
  } //if
  else vCameraPos.y = m_vWorldSize.y/2.0f; //center vertically

  m_pRenderer->SetCameraPos(vCameraPos); //camera to player
} //FollowCamera

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation.

void CGame::ProcessGameState() {
    static float t = 0;
    switch (m_eGameState) {
    case eGameState::Playing:
        if (m_pPlayer == nullptr)
        {
            m_eGameState = eGameState::Menu;
            t = m_pTimer->GetTime();
        }
        else
            if (m_pShop->IsDisplaying())
                m_eGameState = eGameState::Shop;
        break;
    case eGameState::Menu:
        if (m_pTimer->GetTime() - t > .01f)
            BeginGame();
        break;

    case eGameState::Shop:
        if (!m_pShop->IsDisplaying())
            m_eGameState = eGameState::Playing;
        break;
    } //switch
} //ProcessGameState

void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  ControllerHandler(); //handle controller input
  
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  
  m_pTimer->Tick([&](){ //all time-dependent function calls should go here
    if(m_eGameState == eGameState::Playing) m_pObjectManager->move(); //move all objects
    m_pObjectManager->CheckBuffs(); //check for buffs, and apply them
    m_pObjectManager->Update();
    FollowCamera(); //make camera follow player
    m_pParticleEngine->step(); //advance particle animation
  });

  ProcessGameState();
  RenderFrame(); //render a frame of animation
} //ProcessFrame