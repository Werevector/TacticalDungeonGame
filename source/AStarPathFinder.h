#pragma once
#include "Utils.h"
#include "GameMap.h"
#include <memory>

class AStarPathFinder {
	
public:

	AStarPathFinder() {}
	bool FindPath(utility::Point2d position ,utility::Point2d destination);
	void SetMap(GameMap* mapPtr);

private:

	GameMap* mMapPtr;
	utility::Point2d mCurrentDestination;

};