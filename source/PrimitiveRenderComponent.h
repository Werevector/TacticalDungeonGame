#pragma once
#include "ActorComponent.h"
#include "sdl.h"

class PrimitiveRenderComponent : public ActorComponent {
	
	friend class ActorFactory;

public:

	PrimitiveRenderComponent() {}

	PrimitiveRenderComponent(SDL_Renderer* r, SDL_Color c, SDL_Rect t) 
	{ 
		renderHandle	= r;
		renderColor		= c;
		renderTarget	= t;
	}

	void Update(int framedelta) override;

protected:

	

private:
	SDL_Renderer*	renderHandle;
	SDL_Color		renderColor;
	SDL_Rect		renderTarget;
};