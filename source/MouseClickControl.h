#pragma once
#include "Actor.h"
#include "sdl.h"

class MouseClickControl : public ActorComponent {
public:

	void Init() override;
	void PostInit() override;
	void Update(float framedelta) override;
	void HandleMouseClickEvent(SDL_Event* clickEvent);
protected:

private:

};