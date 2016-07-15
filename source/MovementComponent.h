#pragma once
#include "Actor.h"
#include "sdl.h"
#include "MoveActorEvtData.h"
#include "Utils.h"

class MovementComponent : public ActorComponent {

	friend class ActorFactory;

public:

	MovementComponent();
	void Init() override;
	void PostInit() override;
	void Update(float framedelta) override;
	utility::Point2d GetPos();
	void SetPos(float, float);
	void SetVelocity(float, float);
	void SetAcceleration(float, float);

	void ActorMoveDelegate(IEventDataPtr eventDataPtr);

protected:



private:

	float mPosX;
	float mPosY;
	float mVelocityX;
	float mVelocityY;
	float mAccelX;
	float mAccelY;



};