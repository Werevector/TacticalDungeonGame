#pragma once
#include "Actor.h"
#include "sdl.h"
#include "EventData.h"
#include "Utils.h"
#include <memory>
#include "ClickedOnScreenEvtData.h"
#include "MovementComponent.h"

class MouseClickControl : public ActorComponent {
public:

	void Init() override;
	void PostInit() override;
	void Update(float framedelta) override;
	void ClickedOnScreenDelegate(IEventDataPtr eventDataPtr);

protected:

private:

	Point2d mCurrentTarget;
	bool arrived = true;

};