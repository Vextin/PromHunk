/// \file ObstacleManager.cpp

#pragma once
#include "ObstacleManager.h"



CObstacleManager::CObstacleManager()
{
	prob = 0.01f;
}
CObstacleManager::~CObstacleManager()
{

};

// Map grid is traversed, column first
void CObstacleManager::genMapObstacles()
{
	for (int i = 0; i < nheight; i++) //grid row
	{
		for (int j = 0; j < nwidth; j++) //grid column
		{
			prob = 0.01f;
			if (i < 3 || j < 3)
			{
				checkNeighbour(i, j, std::min(i, j));
			}
			else
				checkNeighbour(i, j, 3);
				createObstacle(i, j);

		}
	}
}

void CObstacleManager::createObstacle(int x, int y)
{
	if (float(m_pRandom->randn(0, 100)) / 100.0f < prob)
	{
		switch (m_pRandom->randn(1, 3))
		{
		case 1: obstObjArr[y][x] = m_pObjectManager->create(eSprite::Basketball, Vector2(float(x) * tilesize, float(y) * tilesize)); break;
		case 2: obstObjArr[y][x] = m_pObjectManager->create(eSprite::WeightPlates, Vector2(float(x) * tilesize, float(y) * tilesize)); break;
		case 3: obstObjArr[y][x] = m_pObjectManager->create(eSprite::Dumbells, Vector2(float(x) * tilesize, float(y) * tilesize)); break;
		}
		obstTypeArr[y][x] = 1;
	}
}

void CObstacleManager::checkNeighbour(int y, int x, int d)
{
	if (d == 1)
	{
		//left or above
		if (obstTypeArr[y][x - 1] == 0 || obstTypeArr[y - 1][x] == 0)
			prob += 0.0005;
		//diagnolly left and above
		else if (obstTypeArr[y - 1][x - 1] == 0)
			prob += 0.00025;
	}
	if (d == 2)
	{
		//left or above
		if (obstTypeArr[y][x - 2] == 0 || obstTypeArr[y - 2][x] == 0)
			prob += 0.0005;
		//diagnolly left and above
		else if (obstTypeArr[y - 2][x - 2] == 0)
			prob += 0.00025;
	}
	if (d == 3)
	{
		//left or above
		if (obstTypeArr[y][x - 3] == 0 || obstTypeArr[y - 3][x] == 0)
			prob += 0.0005;
		//diagnolly left and above
		else if (obstTypeArr[y - 3][x - 3] == 0)
			prob += 0.00025;
	}
}

// given a vector pos, get the x, y in the grid
int CObstacleManager::getxCoords(const Vector2& pos)
{
	return int(pos.x / tilesize);
}

int CObstacleManager::getyCoords(const Vector2& pos)
{
	return int(pos.y / tilesize);
}

// given an vector2 pos, get xy pair for a*
Pair CObstacleManager::getxyPair(const Vector2& pos)
{
	int x = int(pos.x / tilesize);
	int y = int(pos.y / tilesize);
	return Pair(y, x);
}

Vector2 CObstacleManager::getVector(const Pair& point)
{
	float x = float(point.second * tilesize) + tilesize / 2;
	float y = float(point.first * tilesize) + tilesize / 2;
	return Vector2(x, y);
}


// Following is adapted from:
// https://www.geeksforgeeks.org/a-search-algorithm/

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.

bool CObstacleManager::isValid(const Pair& point)
{ // Returns true if row number and column number is in
  // range
	if (nwidth > 0 && nheight > 0)
		return (point.first >= 0) && (point.first < nheight)
		&& (point.second >= 0)
		&& (point.second < nwidth);

	return false;
}

// A Utility Function to check whether the given cell is
// blocked or not
bool CObstacleManager::isUnBlocked(const Pair& point)
{
	// Returns true if the cell is not blocked else false
	if (isValid(point) && obstTypeArr[point.first][point.second] == 0)
		return true;
	else
		return false;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool CObstacleManager::isDestination(const Pair& position, const Pair& dest)
{
	return position == dest;
}

// A Utility Function to calculate the 'h' heuristics.
double CObstacleManager::calculateHValue(const Pair& src, const Pair& dest)
{
	// h is estimated with the two points distance formula
	return sqrt(pow((src.first - dest.first), 2.0)
		+ pow((src.second - dest.second), 2.0));
}

// A Utility Function to trace the path from the source to
// destination
void CObstacleManager::tracePath(const std::array<std::array<cell, nwidth>, nheight>& cellDetails, const Pair& dest)
{
	/*printf("\nThe Path is ");*/

	std::stack<Pair> Path;

	int row = dest.first;
	int col = dest.second;
	Pair next_node = cellDetails[row][col].parent;
	do {
		Path.push(next_node);
		path2targ.push(next_node);
		next_node = cellDetails[row][col].parent;
		row = next_node.first;
		col = next_node.second;
	} while (cellDetails[row][col].parent != next_node);

	Path.emplace(row, col);
	path2targ.emplace(row, col);
	while (!Path.empty()) {
		Pair p = Path.top();
		Path.pop();
		//printf("-> (%d,%d) ", p.first, p.second);
	}
}

// A Function to find the shortest path between a given
// source cell to a destination cell according to A* Search
// Algorithm
void CObstacleManager::aStarSearch(const Pair& src, const Pair& dest)
{
	// If the source is out of range
	if (!isValid(src)) {
		//printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (!isValid(dest)) {
		//printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (!isUnBlocked(src)
		|| !isUnBlocked(dest)) {
		//printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src, dest)) {
		//printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	bool closedList[nheight][nwidth];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details
	// of that cell
	std::array<std::array<cell, nwidth>, nheight> cellDetails;

	int i, j;
	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent = { i, j };

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of tuple.*/
	std::priority_queue<Tuple, std::vector<Tuple>,
		std::greater<Tuple> >
		openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.emplace(0.0, i, j);

	// We set this boolean value as false as initially
	// the destination is not reached.
	while (!openList.empty()) {
		const Tuple& p = openList.top();
		// Add this vertex to the closed list
		i = std::get<1>(p); // second element of tuple
		j = std::get<2>(p); // third element of tuple

		// Remove this vertex from the open list
		openList.pop();
		closedList[i][j] = true;
		/*
				Generating all the 8 successor of this cell
					  N.W N N.E
						\ | /
						\ | /
					W----Cell----E
						/ | \
						/ | \
					  S.W S S.E

				Cell-->Popped Cell (i, j)
				N --> North     (i-1, j)
				S --> South     (i+1, j)
				E --> East     (i, j+1)
				W --> West         (i, j-1)
				N.E--> North-East (i-1, j+1)
				N.W--> North-West (i-1, j-1)
				S.E--> South-East (i+1, j+1)
				S.W--> South-West (i+1, j-1)
		*/
		for (int add_x = -1; add_x <= 1; add_x++) {
			for (int add_y = -1; add_y <= 1; add_y++) {
				Pair neighbour(i + add_x, j + add_y);
				// Only process this cell if this is a valid
				// one
				if (isValid(neighbour))
				{
					// If the destination cell is the same
					// as the current successor
					if (isDestination(neighbour, dest))
					{ // Set the Parent of the destination cell
						cellDetails[neighbour.first][neighbour.second].parent = { i, j };
						//printf("The destination cell is found\n");
						tracePath(cellDetails, dest);
						return;
					}
					// If the successor is already on the
					// closed list or if it is blocked, then
					// ignore it.  Else do the following
					else if (!closedList[neighbour.first][neighbour.second] && isUnBlocked(neighbour))
					{
						double gNew, hNew, fNew;
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(neighbour, dest);
						fNew = gNew + hNew;

						// If it isn’t on the open list, add
						// it to the open list. Make the
						// current square the parent of this
						// square. Record the f, g, and h
						// costs of the square cell
						//             OR
						// If it is on the open list
						// already, check to see if this
						// path to that square is better,
						// using 'f' cost as the measure.
						if (cellDetails[neighbour.first][neighbour.second].f == -1
							|| cellDetails[neighbour.first][neighbour.second].f > fNew)
						{
							openList.emplace(fNew, neighbour.first, neighbour.second);

							// Update the details of this
							// cell
							cellDetails[neighbour.first][neighbour.second].g = gNew;
							cellDetails[neighbour.first][neighbour.second].h = hNew;
							cellDetails[neighbour.first][neighbour.second].f = fNew;
							cellDetails[neighbour.first][neighbour.second].parent = { i, j };
						}
					}
				}
			}
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	//printf("Failed to find the Destination Cell\n");
}