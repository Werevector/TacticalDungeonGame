#include "AStarPathFinder.h"

#define STRAIGHT_COST 10
#define DIAG_COST 14

bool AStarPathFinder::FindPath(utility::Point2d position, utility::Point2d destination)
{
	bool pathFound = false;

	if(mMapPtr != NULL)
	{
		pathFound = _FindPath(position, destination);
	}
	return pathFound;
}

void AStarPathFinder::SetMap(GameMap * mapPtr)
{
	mMapPtr = mapPtr;
}

bool AStarPathFinder::_FindPath(utility::Point2d position, utility::Point2d destination)
{
	bool pathFound = false;

	std::list<ASTSquare> openlist;
	std::list<ASTSquare> closedlist;


	
	return pathFound;
}

int AStarPathFinder::Heuristic(utility::Point2d position, utility::Point2d destination)
{
	//Manhattan Heuristic
	int x = abs(floor(destination.x - position.x));
	int y = abs(floor(destination.y - position.y));

	return x + y;
}

void AStarPathFinder::AddAdjacent(std::list<ASTSquare>& sqList, utility::Point2d point)
{

}
