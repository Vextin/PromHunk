/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"

/// \brief The object manager.
///
/// A collection of all of the game objects.

class CObjectManager :
    public LBaseObjectManager<CObject>,
    public CCommon,
    public LSettings
{
private:
    struct EnemyStruct {
        int BasicShooter = 1;
        int BasicRunner = 1;
        int Cheerleader = 1;
        int Footballer = 1;
        int PromQueen = 0;
    } EnemyCount, MaxEnemyCount;
    int CurrentEnemyCount = 0; //current number of all types of enemies
    int TotalEnemyCount = 0; //max number of enemies we want on screen
    int WaveNumber = 0;
    bool BossWave = false;
    float WaveTimer = 0.0f;
    float RefillTimer = 9.0f;

    void BroadPhase(); ///< Broad phase collision detection and response.
    void NarrowPhase(CObject*, CObject*); ///< Narrow phase collision detection and response.
    bool AtWorldEdge(CObject*, Vector2&, float&) const; ///< Test whether at the edge of the world.

    void SpawnEnemy(float x, float y, int z);
    void SpawnNearPlayer(int z);
    float RandomNegative();

public:
    CObjectManager(); //Constructor
    static int totalEnemiesKilled;
    static int enemiesKilled;
    static int nextShopEnemyCount;
    CObject* create(eSprite, const Vector2&); ///< Create new object.
    CObject* createBullet(eSprite, const Vector2&, float damage=1.f, bool isEnemyBullet=false); ///< Create new object.
    void FireGun(CObject*, eSprite); ///Default enemy weapon
    void PlayerDefaultWeapon(CObject*, eSprite);///Default player weapon
    void PlayerTestShotgun(CObject*, eSprite);

    void CheckBuffs();

    void ResetWaveManager();
    void StartWaveManager();
    void CheckEnemies();    //called when Refill happens
    void WaveManager();     //needs to be called whenever we want data for next wave
    void SpawnNextWave();   //called on ~30s timer
    void RefillWave();      //called on ~9s timer
    void Update();
}; //CObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__