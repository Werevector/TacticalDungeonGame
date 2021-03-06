#pragma once
#include "Utils.h"
#include "GameMap.h"
#include <memory>
#include <list>
#include <vector>
#include <set>

class ASTSquare {
public:
	ASTSquare() {}
	ASTSquare(int g) : G(g) {}
	ASTSquare(int g, int h) : G(g), H(h) {}
	ASTSquare(int g, int h, int f) : G(g), H(h), F(f) {}
	ASTSquare(utility::Point2d pos) : mPos(pos) {}

	ASTSquare* mParent;

	utility::Point2d mPos;
	int G;
	int H;
	int F;
};

class AStarPathFinder {
	
public:

	AStarPathFinder() {}
	AStarPathFinder(GameMap* map) { SetMap(map); }
	
	bool FindPath(utility::Point2d position ,utility::Point2d destination);
	void PrintPath();
	void SetMap(GameMap* mapPtr);

private:

	bool _FindPath(utility::Point2d position, utility::Point2d destination);
	int Heuristic(utility::Point2d position, utility::Point2d destination);
	void AddAdjacent(std::list<ASTSquare>& sqList, utility::Point2d point);
	GameMap* mMapPtr;
	utility::Point2d mCurrentDestination;
	std::vector<int> pathToDestination;


};