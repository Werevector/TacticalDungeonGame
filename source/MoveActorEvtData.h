#pragma once
#include "EventData.h"
#include "Utils.h"

class MoveActorEvtData : public BaseEventData
{
	utility::Point2d mPoint;
public:

	static const EventType mEventType;

	explicit MoveActorEvtData(utility::Point2d point) : mPoint(point) {}

	virtual const EventType& VGetEventType(void) const
	{
		return mEventType;
	}

	virtual IEventDataPtr VCopy(void) const
	{
		return IEventDataPtr(std::make_shared<MoveActorEvtData>(MoveActorEvtData(mPoint)));
	}

	virtual const char* GetName(void) const
	{
		return "MoveActorEvtData";
	}

	utility::Point2d GetPosition(void) { return mPoint; }

};

const EventType MoveActorEvtData::mEventType(0x19a857aa);