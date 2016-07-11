#pragma once
#include "ActorComponent.h"
#include "sdl.h"

class MovementComponent : public ActorComponent {

	friend class ActorFactory;

public:

	MovementComponent();
	void Init() override;
	void PostInit() override;
	void Update(int framedelta) override;
	void SetPos(int, int);

protected:



private:

	float mPosX;
	float mPosY;
	float mVelocityX;
	float mVelocityY;
	float mAccelX;
	float mAccelY;



};