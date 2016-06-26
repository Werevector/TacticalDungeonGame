#pragma once
#include "sdl.h"
#include <map>
#include "Actor.h"
#include "ActorFactory.h"
#include "SDLGameWindow.h"

class GameLogic {

public:

	bool Init();
	bool InitTestVersion();
	
	void Run();

	SDL_Renderer*	renderHandle;
	SDL_Window*		windowHandle;

private:

	std::map<unsigned int, Actor> actor_map;
	bool LoadAndAddActor(std::string filepath);
	ActorFactory actorFactory;
	SDL_Event* event;
	SDLGameWindow gameWindow;
	void Update(int framedelta);

	void HandleWindowEvents();


	bool quit = false;


};