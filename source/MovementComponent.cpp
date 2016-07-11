#include "MovementComponent.h"
#include "IsometricSpriteRenderer.h"

MovementComponent::MovementComponent()
{
	mPosX		= 0;
	mPosY		= 0;
	mVelocityX	= 0;
	mVelocityY	= 0;
	mAccelX		= 0;
	mAccelY		= 0;
}

void MovementComponent::Init()
{
}

void MovementComponent::PostInit()
{
}

void MovementComponent::Update(float framedelta)
{
	mVelocityX += mAccelX;
	mVelocityY += mAccelY;
	
	mPosX += mVelocityX * framedelta;
	mPosY += mVelocityY * framedelta;

	auto ownerStrongPtr = std::shared_ptr<Actor>(ownerPtr);

	auto componentPtr = ownerStrongPtr->FindComponent("IsometricSpriteRenderer");
	if(componentPtr != nullptr)
	{
		auto isr = std::static_pointer_cast<IsometricSpriteRenderer>(componentPtr);
		isr->SetPos(mPosX, mPosY);
	}
	
	
}

void MovementComponent::SetPos(float newX, float newY)
{
	mPosX = newX;
	mPosY = newY;
}

void MovementComponent::SetVelocity(float newVelX, float newVelY)
{
	mVelocityX = newVelX;
	mVelocityY = newVelY;
}

void MovementComponent::SetAcceleration(float newAccX, float newAccY)
{
	mAccelX = newAccX;
	mAccelY = newAccY;
}
