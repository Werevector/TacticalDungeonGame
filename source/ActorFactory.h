#pragma once
#include "Actor.h"
#include "json.hpp"
#include "sdl.h"
#include "GameMap.h"
#include "IsoSpriteRenderComponent.h"
#include "MovementComponent.h"
#include "MouseClickControlComponent.h"
#include <iostream>
#include <fstream>
#include <map>

typedef ActorComponent* (*pfunc)(nlohmann::basic_json<>& component);

class ActorFactory {
public:

	ActorFactory();
	SDL_Renderer* renderHandle;
	std::shared_ptr<Actor> CreateActorFromFile(std::string filepath);

private:

	std::map<std::string, 
			 std::function<std::shared_ptr<ActorComponent>(nlohmann::basic_json<>&)>>
			 componentCreatorMap;

	void PopulateComponents(std::string filepath, std::shared_ptr<Actor>);

	int actorIdCounter = 0;
	int componentIdCounter = 0;

	int getNextActorId()
	{
		actorIdCounter++;
		return actorIdCounter;
	}

	int getNextComponentId()
	{
		componentIdCounter++;
		return componentIdCounter;
	}
};