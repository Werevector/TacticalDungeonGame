#pragma once
#include "Actor.h"
#include "Utils.h"
#include "EventManager.h"
#include "EventData.h"

class PathFinderComponent : public ActorComponent {

public:

	PathFinderComponent();
	~PathFinderComponent();

	void NewTargetDelegate(IEventDataPtr dataPtr);

private:

	//Find path to targetpoint
	bool FindPath();

	utility::Point2d mTargetPoint;
	

};