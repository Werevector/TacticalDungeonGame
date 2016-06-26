#include "GameLogic.h"

bool GameLogic::Init()
{
	return false;
}

bool GameLogic::InitTestVersion()
{
	gameWindow.Init();
	gameWindow.flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	gameWindow.CreateGameWindowAndRenderer();
	gameWindow.versionPrint();
	actorFactory.renderHandle = gameWindow.renderHandle;

	event = new SDL_Event();
	
	std::string basepath = "F:\\Programming\\C++\\Git\\ActorSystem\\resources\\actors\\";
	LoadAndAddActor(basepath + "actor.json");

	return true;
}

void GameLogic::Update(int framedelta)
{
	for(auto& actor : actor_map)
	{
		actor.second.Update(framedelta);
	}
}

void GameLogic::Run()
{
	while (!quit) {
		gameWindow.Clear();
		HandleWindowEvents();
		Update(1);
		gameWindow.SwapBuffer();
	}

}

void GameLogic::HandleWindowEvents() {
	while (SDL_PollEvent(event) != NULL) {
		if (event->type == SDL_QUIT) {
			quit = true;
		}
	}
}

bool GameLogic::LoadAndAddActor(std::string filepath)
{
	bool success = true;

	Actor actor = actorFactory.CreateActorFromFile(filepath);
	actor_map.emplace(actor.GetActorId(), actor);

	return success;
}

