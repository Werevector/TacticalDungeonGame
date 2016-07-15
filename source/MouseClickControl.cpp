#include "MouseClickControl.h"
#include "EventHandler.h"

void MouseClickControl::Init()
{
}

void MouseClickControl::PostInit()
{
	EventListenerDelegate delegateFunction(this, &MouseClickControl::ClickedOnScreenDelegate);
	IEventManager::Get()->VAddListener(delegateFunction, ClickedOnScreenEvtData::mEventType);
}

void MouseClickControl::Update(float framedelta)
{

}

void MouseClickControl::ClickedOnScreenDelegate(IEventDataPtr eventDataPtr)
{
	std::shared_ptr<ClickedOnScreenEvtData> castEventDataPtr =
		std::static_pointer_cast<ClickedOnScreenEvtData>(eventDataPtr);

	mCurrentTarget = castEventDataPtr->GetPosition();
}
