#include "EventManager.h"
#include "sdl.h"

//-------------------------------------------------------------------------------------
// IEventManager
//-------------------------------------------------------------------------------------
static IEventManager* gEventManagerPtr = NULL;

IEventManager* IEventManager::Get(void)
{
	return gEventManagerPtr;
}

IEventManager::IEventManager(const char* namePtr, bool setAsGlobal)
{
	if (setAsGlobal)
	{
		if (gEventManagerPtr)
		{
			delete gEventManagerPtr;
		}

		gEventManagerPtr = this;
	}
}

IEventManager::~IEventManager(void)
{
	if (gEventManagerPtr == this)
		gEventManagerPtr = NULL;
}

//-------------------------------------------------------------------------------------
// EventManager
//-------------------------------------------------------------------------------------
EventManager::EventManager(const char * namePtr, bool setAsGlobal) : IEventManager(namePtr, setAsGlobal)
{
	mActiveQueue = 0;
}

bool EventManager::VAddListener(const EventListenerDelegate & eventDelegate, const EventType & type)
{
	EventListenerList& eventListenerList = mEventListeners[type];

	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	{
		if (eventDelegate == (*it))
		{
			std::cout << "ERROR : Attempting to double-register a delegate\n";
			return false;
		}
	}

	eventListenerList.push_back(eventDelegate);
	return true;

}

bool EventManager::VRemoveListener(const EventListenerDelegate & eventDelegate, const EventType & type)
{
	bool success = false;

	auto findIt = mEventListeners.find(type);
	if (findIt != mEventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				break;
			}
		}
	}
	return success;
}

bool EventManager::VTriggerEvent(const IEventDataPtr & pEvent)
{
	bool processed = false;

	auto findIt = mEventListeners.find(pEvent->VGetEventType());
	if (findIt != mEventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;

		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			listener(pEvent); //Invoke delegate
			processed = true;
		}
	}
	return processed;
}

bool EventManager::VQueueEvent(const IEventDataPtr & pEvent)
{
	auto findIt = mEventListeners.find(pEvent->VGetEventType());
	if (findIt != mEventListeners.end())
	{
		mQueues[mActiveQueue].push_back(pEvent);
		return true;
	}
	else
	{
		return false;
	}
}

bool EventManager::VAbortEvent(const EventType & type, bool allOfType)
{
	bool success = false;
	EventListenerMap::iterator findIt = mEventListeners.find(type);

	if (findIt != mEventListeners.end())
	{
		EventQueue& eventQueue = mQueues[mActiveQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			auto thisIt = it;
			++it;
			if ((*thisIt)->VGetEventType() == type)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}
	return success;
}

bool EventManager::VTickVUpdate(unsigned long maxMillis)
{
	unsigned long currMs = SDL_GetTicks();
	unsigned long maxMs = ( (maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis) );
	
	//swap queues and clear
	int queueToProcess = mActiveQueue;
	mActiveQueue = (mActiveQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	mQueues[mActiveQueue].clear();

	while( !mQueues[queueToProcess].empty())
	{
		IEventDataPtr pEvent = mQueues[queueToProcess].front();
		mQueues[queueToProcess].pop_front();
		
		const EventType& eventType = pEvent->VGetEventType();

		auto findIt = mEventListeners.find(eventType);
		if (findIt != mEventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				listener(pEvent);
			}
		}

		//check if time ran out
		currMs = SDL_GetTicks();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			std::cout << "Aborting event processing, time ran out\n";
			break;
		}
	}
	
	//If time ran out, push remaining to new queue
	bool queueFlushed = (mQueues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!mQueues[queueToProcess].empty()) 
		{
			IEventDataPtr pEvent = mQueues[queueToProcess].back();
			mQueues[queueToProcess].pop_back();
			mQueues[mActiveQueue].push_front(pEvent);
		}
	}
	return queueFlushed;


}

