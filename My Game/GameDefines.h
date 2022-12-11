/// \file GameDefines.h
/// \brief Game specific defines.

#ifndef __L4RC_GAME_GAMEDEFINES_H__
#define __L4RC_GAME_GAMEDEFINES_H__

#include "Defines.h"

/// \brief Sprite enumerated type.
///
/// An enumerated type for the sprites, which will be cast to an unsigned
/// integer and used for the index of the corresponding texture in graphics
/// memory. `Size` must be last.

enum class eGameState {
	Menu, Playing, Shop
}; //eGameState

enum class eSprite: UINT{
  Background, Bullet, Bullet2, Player, BasicShooterEnemy, 
  Smoke, Spark, BasicRunnerEnemy, CheerleaderEnemy, Dummy, Crosshair, GameOver, PromQueenEnemy, FootballerEnemy,
  HealthBarRD, HealthBarGR,

  PlayerSheet, RunmanSheet, CheerleaderSheet, ShooterSheet,
  //Keeping shop cards together for cleanliness
  ShopCard_Damage1,
  ShopCard_Blank,
  Size  //MUST BE LAST
}; //eSprite

/// \brief Sound enumerated type.
///
/// An enumerated type for the sounds, which will be cast to an unsigned
/// integer and used for the index of the corresponding sample. `Size` must 
/// be last.

enum class eSound: UINT{
  Clang, Grunt, Gun, Ricochet,
  Size  //MUST BE LAST
}; //eSound

#endif //__L4RC_GAME_GAMEDEFINES_H__
