#pragma once
#include "sdl.h"
#include <map>
#include "Actor.h"
#include "ActorFactory.h"
#include "SDLGameWindow.h"
#include "GameMap.h"
#include "Camera.h"
#include "FastDelegate.h"
#include "FastDelegateBind.h"
#include "Utils.h"
#include "ClickedOnScreenEvtData.h"
#include "EventHandler.h"

class GameLogic {

public:

	GameLogic() {};

	bool Init();
	bool InitTestVersion();
	
	void Run();

private:
	bool LoadAndAddActor(std::string filepath);
	void Update(float framedelta);
	void HandleWindowEvents();

	std::map<unsigned int, std::shared_ptr<Actor>> actors;
	
	ActorFactory actorFactory;
	SDL_Event* event;
	SDLGameWindow gameWindow;
	
	GameMap gameMap;

	Camera mGameCamera;

	bool quit = false;
	Uint32 TicksNow;
	Uint32 TicksLast;

};