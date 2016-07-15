#include "MouseClickControlComponent.h"
#include "EventManager.h"

void MouseClickControlComponent::Init()
{
}

void MouseClickControlComponent::PostInit()
{
	EventListenerDelegate delegateFunction(this, &MouseClickControlComponent::ClickedOnScreenDelegate);
	auto test = IEventManager::Get();
	IEventManager::Get()->VAddListener(delegateFunction, ClickedOnScreenEvtData::mEventType);
}

void MouseClickControlComponent::Update(float framedelta)
{

	float vx = 0; float vy = 0;
	float speed = 100.f;
	float area = 1.f;
	bool arrivedX = false; bool arrivedY = false;
	utility::Point2d currPos;

	auto ownerStrongPtr = std::shared_ptr<Actor>(ownerPtr);
	auto componentPtr = ownerStrongPtr->FindComponent("MovementComponent");
	if (componentPtr != nullptr)
	{
		if (!arrived)
		{
			auto movecomp = std::static_pointer_cast<MovementComponent>(componentPtr);
			currPos = movecomp->GetPos();
			if (currPos.x < mCurrentTarget.x - area)
			{
				vx += speed;

			}
			else if (currPos.x > mCurrentTarget.x + area)
			{
				vx -= speed;
			}
			else {
				arrivedX = true;
			}

			if (currPos.y < mCurrentTarget.y - area)
			{
				vy += speed;
			}
			else if (currPos.y > mCurrentTarget.y + area)
			{
				vy -= speed;
			}else
			{
				arrivedY = true;
			}
			movecomp->SetVelocity(vx, vy);
			if (arrivedX && arrivedY) arrived = true;
		}
	}
}

void MouseClickControlComponent::ClickedOnScreenDelegate(IEventDataPtr eventDataPtr)
{
	auto ownerStrongPtr = std::shared_ptr<Actor>(ownerPtr);
	std::cout << "ClickedOnScreenEvent Actor id: " << ownerStrongPtr->GetActorId() << "\n\n";
	std::shared_ptr<ClickedOnScreenEvtData> castEventDataPtr =
		std::static_pointer_cast<ClickedOnScreenEvtData>(eventDataPtr);

	mCurrentTarget = castEventDataPtr->GetPosition();
	arrived = false;

}
