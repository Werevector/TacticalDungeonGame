#pragma once
#include "EventData.h"
#include "Utils.h"

class ClickedOnScreenEvtData : public BaseEventData
{
	utility::Point2d mPoint;
public:

	static const EventType mEventType;

	explicit ClickedOnScreenEvtData(utility::Point2d point) : mPoint(point) {}

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

	utility::Point2d GetPosition(void) { return mPoint; }

};

const EventType ClickedOnScreenEvtData::mEventType(0x421791eb);