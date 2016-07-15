#pragma once
#include "EventData.h"
#include "Utils.h"

class MoveActorEvtData : public BaseEventData
{
	Point2d mPoint;
public:

	static const EventType mEventType;

	explicit MoveActorEvtData(Point2d point) : mPoint(point) {}

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

	Point2d GetPosition(void) { return mPoint; }

};