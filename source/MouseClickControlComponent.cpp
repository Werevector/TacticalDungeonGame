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

	mPathFinder.SetMap(mGameMapPtr);

}

void MouseClickControlComponent::Update(float framedelta)
{

	/*float vx = 0; float vy = 0;
	float speed = 10;
	float area = 0.1f;
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
	}*/
}

void MouseClickControlComponent::ClickedOnScreenDelegate(IEventDataPtr eventDataPtr)
{
	system("cls");
	auto ownerStrongPtr = std::shared_ptr<Actor>(ownerPtr);
	std::cout << "ClickedOnScreenEvent Actor id: " << ownerStrongPtr->GetActorId() << "\n\n";
	
	std::shared_ptr<ClickedOnScreenEvtData> castEventDataPtr =
		std::static_pointer_cast<ClickedOnScreenEvtData>(eventDataPtr);
	
	utility::Point2d clickPos = castEventDataPtr->GetPosition();
	clickPos.x += mCameraPtr->mPositionX;
	clickPos.y += mCameraPtr->mPositionY;
	utility::Point2d clickPosMap = utility::IsoToOrtho(clickPos);
	clickPosMap.x = floor(clickPosMap.x);
	clickPosMap.y = floor(clickPosMap.y);

	auto componentPtr = ownerStrongPtr->FindComponent("MovementComponent");
	
	auto movecomp = std::static_pointer_cast<MovementComponent>(componentPtr);
	auto currPos = movecomp->GetPos();
	utility::Point2d playerPosMap = utility::IsoToOrtho(currPos);
	playerPosMap.x = floor(playerPosMap.x);
	playerPosMap.y = floor(playerPosMap.y);

	std::cout << "clicked_x: " << clickPosMap.x << "\t" << "clicked_y: " << clickPosMap.y << std::endl;


	bool found = mPathFinder.FindPath(playerPosMap, clickPosMap);
	
	if (found) {
		std::cout << "Path was found:\n";
		mPathFinder.PrintPath();
		std::cout << std::endl;
	}
	//utility::Point2d pos = castEventDataPtr->GetPosition();
	//
	//std::cout << "screen x: " << pos.x << "\t\t screen y: " << pos.y << std::endl;
	//
	////translate to worldspace
	//pos.x += mCameraPtr->mPositionX;
	//pos.y += mCameraPtr->mPositionY;
	//std::cout << "world x: " << pos.x << "\t\t world y: " << pos.y << std::endl;

	//utility::Point2d isoPoint = utility::IsoToOrtho(pos);
	//std::cout << "ortho x: " << isoPoint.x << "\t ortho y: " << isoPoint.y << "\n\n";

	//mCurrentTarget.x = floor(isoPoint.x);
	//mCurrentTarget.y = floor(isoPoint.y);

	//arrived = false;

}

void MouseClickControlComponent::SetCamera(Camera * c)
{
	mCameraPtr = c;
}
