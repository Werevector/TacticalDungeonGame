#pragma once
#include "Actor.h"
#include "sdl.h"
#include "EventData.h"
#include "Utils.h"
#include <memory>
#include "ClickedOnScreenEvtData.h"
#include "MovementComponent.h"
#include "Camera.h"
#include "AStarPathFinder.h"
#include <math.h>

class MouseClickControlComponent : public ActorComponent {
public:

	void Init() override;
	void PostInit() override;
	void Update(float framedelta) override;
	void ClickedOnScreenDelegate(IEventDataPtr eventDataPtr);
	void SetCamera(Camera* c);

	AStarPathFinder mPathFinder;
	GameMap* mGameMapPtr;

protected:

private:
	utility::Point2d mCurrentTarget;
	bool arrived = true;
	Camera* mCameraPtr;
	
	

};