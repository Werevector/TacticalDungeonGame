#include "MouseClickControl.h"

void MouseClickControl::Init()
{
}

void MouseClickControl::PostInit()
{
	
}

void MouseClickControl::Update(float framedelta)
{

}

void MouseClickControl::HandleMouseClickEvent(SDL_Event * clickEvent)
{
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);

	std::cout << "Component recieved clickevent\n x:" << x << "\t" << "y:" << y << std::endl;
}
