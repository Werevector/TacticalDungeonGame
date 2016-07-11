#pragma once
#include "Actor.h"
#include "sdl.h"

class MovementComponent : public ActorComponent {

	friend class ActorFactory;

public:

	MovementComponent();
	void Init() override;
	void PostInit() override;
	void Update(int framedelta) override;
	void SetPos(float, float);
	void SetVelocity(float, float);
	void SetAcceleration(float, float);

protected:



private:

	float mPosX;
	float mPosY;
	float mVelocityX;
	float mVelocityY;
	float mAccelX;
	float mAccelY;



};