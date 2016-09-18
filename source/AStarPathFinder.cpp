#include "AStarPathFinder.h"

#define STRAIGHT_COST 10
#define DIAG_COST 99 //14
using namespace utility;

bool AStarPathFinder::FindPath(utility::Point2d position, utility::Point2d destination)
{
	bool pathFound = false;
	pathToDestination.clear();

	if(mMapPtr != NULL)
	{
		pathFound = _FindPath(position, destination);
	}
	return pathFound;
}

void AStarPathFinder::PrintPath()
{
	for (int i = pathToDestination.size() - 1; i >= 0; --i)
	{
		std::cout << " " << pathToDestination[i];
	}
}

void AStarPathFinder::SetMap(GameMap * mapPtr)
{
	mMapPtr = mapPtr;
}

int _FindLowestValueIndex(std::set<int> open, std::vector<int> f)
{
	int index = *open.begin();
	//int min = *open.begin();
	for (int i : open)
	{
		if (f[i] < f[index])
			index = i;
	}
	return index;
}

int _FindLowestValueIndex(std::vector<int> open, std::vector<int> f)
{
	int index = 0;
	for (int i = 1; i < open.size(); ++i)
	{
		if (f[open[i]] < f[index])
			index = open[i];
	}
	return index;
}

bool AStarPathFinder::_FindPath(utility::Point2d position, utility::Point2d destination)
{
	using namespace std;

	vector<vector<int>> relative_a = {
		{ -1, -1 },
		{ -1, 0 },
		{ -1, 1 },
		{ 0, -1 },
		{ 0, 1 },
		{ 1, -1 },
		{ 1, 0 },
		{ 1, 1 }
	};
	
	bool pathFound = false;

	auto weights = mMapPtr->GetWeightLayers();

	int width = mMapPtr->GetMapWidth();
	int height = mMapPtr->GetMapHeight();

	set<int> open;
	set<int> closed;
	vector<int> g(mMapPtr->GetNrOfTilesInLayer(), 0);
	vector<int> h(mMapPtr->GetNrOfTilesInLayer(), 0);
	vector<int> f(mMapPtr->GetNrOfTilesInLayer(), 9999);
	vector<int> parent(mMapPtr->GetNrOfTilesInLayer(), 0);

	int start	= PositionTo1D(position, width);
	int goal	= PositionTo1D(destination, width);
	int selected = 0;

	//Init find
	g[start] = 0;
	h[start] = Heuristic(position, destination);
	f[start] = g[start] + h[start];
	open.insert(start);

	while (!pathFound)
	{
		selected = _FindLowestValueIndex(open, f);
		//selected = *open.begin();
		open.erase(selected);
		closed.insert(selected);
		
		Point2d selpoint = IndexToPosition(selected, width, height);
		//add adjacent to open
		for (vector<int> relative : relative_a)
		{
			int x = selpoint.x + relative[0];
			int y = selpoint.y + relative[1];
			
			//If inside bounds
			if (x >= 0 && x < width && y >= 0 && y < height)
			{
				Point2d newPoint(x, y);
				int newIndex = PositionTo1D(newPoint, width);

				//Store movement cost to new position
				int newcost = 0;
				if (relative[0] == 0 || relative[1] == 0)
					newcost = g[selected] + STRAIGHT_COST;
				else
					newcost = g[selected] + DIAG_COST;

				
				//Only operate on indexes not in closed list
				if (closed.find(newIndex) == closed.end())
				{
					//Check if the new index is already in the open list
					//If so then check if the move from selected is better
					auto found = open.find(newIndex) != open.end();
					if (found)
					{

						//Check if the new move is better, if so update
						if (newcost < g[newIndex])
						{
							g[newIndex] = newcost;
							f[newIndex] = h[newIndex] + newcost;
							parent[newIndex] = selected;
						}
					}
					else
					{
						/*
						Since the index does not exist in open
						check if the new tileposition is walkable
						if so then add it to open and calculate g,h,f
						*/
						if (weights[0][newIndex] != 1)
						{
							g[newIndex] = newcost;
							h[newIndex] = Heuristic(newPoint, destination);
							f[newIndex] = newcost + h[newIndex];
							parent[newIndex] = selected;
							open.insert(newIndex);
						}
					}
				}
			}
			//Relative position was outside bounds
		}
		//End of relative position loop
		
		/*
		Now we check the closed list to see if we have found the destination path
		if it is not found AND the open list is empty, there is no path.
		*/

		if (closed.find(goal) != closed.end())
		{
			int p = goal;
			while (p != start)
			{
				pathToDestination.push_back(p);
				p = parent[p];
			}
			pathToDestination.push_back(start);
			pathFound = true;
		}
		else
		{
			if (open.empty())
			{
				break;
			}
		}
	}


	
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
