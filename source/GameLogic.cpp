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
	gameWindow.flags = SDL_WINDOW_SHOWN;
	gameWindow.CreateGameWindowAndRenderer();
	gameWindow.VersionPrint();
	
	actorFactory.renderHandle = gameWindow.renderHandle;

	mGameCamera.mCameraWidth = gameWindow.windowMetrics.w;
	mGameCamera.mCameraHeight = gameWindow.windowMetrics.h;

	event = new SDL_Event();

	
	LoadAndAddActor("actor.json");
	gameMap.LoadMapFromTmx(gameWindow.renderHandle, paths::PathMaps() + "openpath.tmx");
	

	return true;
}

void GameLogic::Update(int framedelta)
{
	gameMap.RenderMap(gameWindow.renderHandle, &mGameCamera.GetCameraAsRect());
	for(auto& actor : actors)
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
	auto keyboardStates = SDL_GetKeyboardState(NULL);
	if (keyboardStates[SDL_SCANCODE_ESCAPE]) quit = true;
}

bool GameLogic::LoadAndAddActor(std::string filepath)
{
	bool success = true;
	std::string path = paths::PathActors() + filepath;
	Actor actor = actorFactory.CreateActorFromFile(path);
	actors.emplace(actor.GetActorId(), actor);

	return success;
}

