#include "MovementComponent.h"

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

void MovementComponent::Update(int framedelta)
{
	mVelocityX += mAccelX;
	mPosX += mVelocityX;

	mVelocityY += mAccelY;
	mPosY += mVelocityY;
}

void MovementComponent::SetPos(int newX, int newY)
{
	mPosX = newX;
	mPosY = newY;
}
