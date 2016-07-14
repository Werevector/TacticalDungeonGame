#pragma once

#include <ostream>
#include <memory>

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

class IEventManager 
{

public:

	explicit IEventManager(const char* namePtr, bool setAsGlobal);
	virtual ~IEventManager(void);

	virtual bool VAddListener() = 0;

	virtual bool VRemoveListener() = 0;

	virtual bool VTriggerEvent() = 0;

	virtual bool VQueueEvent() = 0;

	virtual bool VAbortEvent() = 0;

	virtual bool VTickVUpdate() = 0;

	static IEventManager* Get(void);
};

class Eventmanager : public IEventManager 
{
public:


};













