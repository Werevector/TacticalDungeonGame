#include "MouseClickControl.h"

void MouseClickControl::Init()
{
}

int MyEventFilter(void* userdata, SDL_Event* event) {
	
	if (event->type == SDL_USEREVENT) {
		std::cout << "UserEvent: " << event->type << std::endl;
	}
	return 1;
}

void MouseClickControl::PostInit()
{
	SDL_AddEventWatch(MyEventFilter, (void*)NULL);
}

void MouseClickControl::Update(float framedelta)
{
	SDL_Event* event = new SDL_Event;
	event->type = SDL_USEREVENT;

	SDL_PushEvent(event);
}
