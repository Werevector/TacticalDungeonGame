#include "GameLogic.h"

bool GameLogic::Init()
{
	return false;
}

bool GameLogic::InitTestVersion()
{

	gameWindow.Init();
	gameWindow.windowMetrics.x = 100;
	gameWindow.windowMetrics.y = 200;
	gameWindow.windowMetrics.w = 800;
	gameWindow.windowMetrics.h = 600;
	gameWindow.windowTitle = "Dungeons n stuff !";
	gameWindow.flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	gameWindow.CreateGameWindowAndRenderer();
	gameWindow.versionPrint();
	
	actorFactory.renderHandle = gameWindow.renderHandle;

	mGameCamera.mCameraWidth = 800;
	mGameCamera.mCameraHeight = 600;

	event = new SDL_Event();

	//LoadAndAddActor(basepathActors + "actor.json");

	gameMap.LoadMapFromTmx(gameWindow.renderHandle, paths::PathMaps() + "empty.tmx");

	return true;
}

void GameLogic::Update(int framedelta)
{
	for(auto& actor : actors)
	{
		actor.second.Update(framedelta);
	}
	gameMap.RenderMap(gameWindow.renderHandle, &mGameCamera.GetCameraAsRect());
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

