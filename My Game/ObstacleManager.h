/// \file ObstacleManager.h
/// \brief Interface for the tile manager ObstacleManager.

#ifndef __L4RC_GAME_OBSTACLEMANAGER_H__
#define __L4RC_GAME_OBSTACLEMANAGER_H__

#include "Common.h"
#include "Component.h"
#include "ObjectManager.h"
#include "ComponentIncludes.h"

#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>

// Following is adapted from:
// https://www.geeksforgeeks.org/a-search-algorithm/

// Creating a shortcut for int, int pair type
typedef std::pair<int, int> Pair;
// Creating a shortcut for tuple<int, int, int> type
typedef std::tuple<double, int, int> Tuple;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    Pair parent;
    // f = g + h
    double f, g, h;
    cell()
        : parent(-1, -1)
        , f(-1)
        , g(-1)
        , h(-1)
    {
    }
};

/// \brief The tile manager.
///
/// The tile manager is responsible for the tile-based obstacles.

class CObstacleManager : LComponent, CCommon
{
private:
    float tilesize = 80.0f; ///< Tile width and height.
    static const int nwidth = 48; ///< Number of tiles wide. 
    static const int nheight = 27; ///< Number of tiles high.
    float prob;
public:
    CObstacleManager(); ///< Constructor.
    ~CObstacleManager(); ///< Destructor.
    void genMapObstacles(); /// populate grid with obstacles
    void createObstacle(int, int); /// randomly create an obsticle at the given location
    void checkNeighbour(int, int, int);
    int obstTypeArr[nwidth][nheight] = {};
    CObject* obstObjArr[nwidth][nheight] = {};
    

    //A* search stuff
    std::stack<Pair> path2targ;
    int getxCoords(const Vector2&);
    int getyCoords(const Vector2&);
    Pair getxyPair(const Vector2&);
    Vector2 getVector(const Pair&);
    bool isValid(const Pair&);
    bool isUnBlocked(const Pair&);
    bool isDestination(const Pair&, const Pair&);
    double calculateHValue(const Pair&, const Pair&);
    void tracePath(const std::array<std::array<cell, nwidth>, nheight>&, const Pair&);
    void aStarSearch(const Pair&, const Pair&);

}; //CObstacleManager

#endif //__L4RC_GAME_OBSTACLEMANAGER_H__