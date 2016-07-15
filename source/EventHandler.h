#pragma once

#include <ostream>
#include <memory>
#include <map>
#include <list>
#include <iostream>
#include "FastDelegate.h"
#include "EventData.h"

typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;

class IEventManager 
{

public:

	enum EConstants {kINFINITE = 0xffffffff};

	explicit IEventManager(const char* namePtr, bool setAsGlobal);
	virtual ~IEventManager(void);

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;

	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) = 0;

	virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;

	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;

	virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE) = 0;

	static IEventManager* Get(void);
};


const unsigned int EVENTMANAGER_NUM_QUEUES = 2;
class EventManager : public IEventManager 
{
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventDataPtr> EventQueue;

	EventListenerMap mEventListeners;
	EventQueue mQueues[EVENTMANAGER_NUM_QUEUES];
	
	int mActiveQueue;

public:

	explicit EventManager(const char* namePtr, bool setAsGlobal);
	virtual ~EventManager(void) {}

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const;
	virtual bool VQueueEvent(const IEventDataPtr& pEvent);
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false);
	virtual bool VTickVUpdate(unsigned long maxMillis = kINFINITE);

};













