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

	
	LoadAndAddActor("player.json");
	LoadAndAddActor("enemy.json");

	gameMap.LoadMapFromTmx(gameWindow.renderHandle, paths::PathMaps() + "openpath.tmx");
	
	TicksNow = SDL_GetTicks();
	TicksLast = TicksNow;

	EventManager evtManager()

	return true;
}

void GameLogic::Update(float framedelta)
{
	gameMap.RenderMap(gameWindow.renderHandle, &mGameCamera.GetCameraAsRect());
	for(auto& actor : actors)
	{
		actor.second->Update(framedelta);
	}
	EventManager::Get()->VTickVUpdate();
	
}

void GameLogic::Run()
{
	while (!quit) {
		gameWindow.Clear();
		HandleWindowEvents();

		float framedelta = 0;
		TicksNow = SDL_GetTicks();
		if (TicksNow > TicksLast) framedelta = float(TicksNow - TicksLast) / 1000;
		
		TicksLast = TicksNow;

		Update(framedelta);
		gameWindow.SwapBuffer();
	}

}

void GameLogic::HandleWindowEvents() {
	
	while (SDL_PollEvent(event) != NULL) {
		switch (event->type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONUP:
			std::cout << "MOUSEBUTTONUP SDL EVENT TRIGGERED\n";
			int x = 0;
			int y = 0;
			SDL_GetMouseState(&x, &y);
			Point2d point;
			point.x = x;
			point.y = y;
			std::shared_ptr<ClickedOnScreenEvtData> clickedEvent = std::make_shared<ClickedOnScreenEvtData>(ClickedOnScreenEvtData(point));
			IEventManager::Get()->VQueueEvent(std::static_pointer_cast<IEventData>(clickedEvent));
			break;
		}
	}

	auto keyboardStates = SDL_GetKeyboardState(NULL);
	if (keyboardStates[SDL_SCANCODE_ESCAPE]) quit = true;

}

bool GameLogic::LoadAndAddActor(std::string filepath)
{
	bool success = true;
	std::string path = paths::PathActors() + filepath;
	std::shared_ptr<Actor> actorPtr = actorFactory.CreateActorFromFile(path);
	actors.emplace(actorPtr->GetActorId(), actorPtr);

	return success;
}

