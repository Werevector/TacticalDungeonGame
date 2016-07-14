#pragma once
#include <memory>

class IEventData;
typedef unsigned long EventType;
typedef std::shared_ptr<IEventData> IEventDataPtr;
class IEventData
{
public:
	virtual const EventType& VGetEventType(void) const = 0;
	virtual float VGetTimeStamp(void) const = 0;

	virtual IEventDataPtr VCopy(void) const = 0;

};

class BaseEventData : public IEventData
{
	const float mTimeStamp;

public:
	explicit BaseEventData(const float timeStamp = 0.0f) : mTimeStamp(timeStamp) {}
	virtual ~BaseEventData(void) {}

	virtual const EventType& VGetEventType(void) const = 0;

	float VGetTimeStamp(void) const { return mTimeStamp; }
};