#pragma once
#include "EventData.h"
#include "Utils.h"

class ClickedOnScreenEvtData : public BaseEventData
{
	Point2d mPoint;
public:

	static const EventType mEventType;

	explicit ClickedOnScreenEvtData(Point2d point) : mPoint(point) {}

	virtual const EventType& VGetEventType(void) const
	{
		return mEventType;
	}

	virtual IEventDataPtr VCopy(void) const
	{
		return IEventDataPtr(std::make_shared<ClickedOnScreenEvtData>(ClickedOnScreenEvtData(mPoint)));
	}

	virtual const char* GetName(void) const
	{
		return "ClickedOnScreenEvtData";
	}

	Point2d GetPosition(void) { return mPoint; }

};