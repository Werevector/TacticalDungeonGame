#include "GameLogic.h"

bool GameLogic::Init()
{
	return false;
}

bool GameLogic::InitTestVersion()
{

	gameWindow.Init();
	gameWindow.windowMetrics.x = 0;
	gameWindow.windowMetrics.y = 25;
	gameWindow.windowMetrics.w = 1900;
	gameWindow.windowMetrics.h = 1000;
	gameWindow.windowTitle = "Dungeons n stuff !";
	gameWindow.flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	gameWindow.CreateGameWindowAndRenderer();
	gameWindow.versionPrint();
	actorFactory.renderHandle = gameWindow.renderHandle;

	event = new SDL_Event();

	//LoadAndAddActor(basepathActors + "actor.json");

	gameMap.LoadMapFromTmx(gameWindow.renderHandle, paths::PathMaps() + "house.tmx");

	return true;
}

void GameLogic::Update(int framedelta)
{
	for(auto& actor : actors)
	{
		actor.second.Update(framedelta);
	}
	gameMap.RenderMap(gameWindow.renderHandle);
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
	actors.emplace(actor.GetActorId(), actor);

	return success;
}

