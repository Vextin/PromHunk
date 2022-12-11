/// \file Common.cpp
/// \brief Code for the class CCommon.
///
/// This file contains declarations and initial values
/// for CCommon's static member variables.

#include "Common.h"

LSpriteRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
LParticleEngine2D* CCommon::m_pParticleEngine = nullptr;
Shop* CCommon::m_pShop = nullptr;
Vector2 CCommon::m_vWorldSize = Vector2::Zero;
CPlayer* CCommon::m_pPlayer = nullptr;
CObstacle* CCommon::m_pObstacle = nullptr;
CEntity* CCommon::m_pTargetDummy = nullptr;
CMouse* CCommon::m_pMouse = nullptr;
bool CCommon::isPaused = false;
bool CCommon::gameOver = false;