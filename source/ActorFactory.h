#pragma once
#include "Actor.h"
#include <iostream>
#include <fstream>
#include <map>
#include "json.hpp"
#include "PrimitiveRenderComponent.h"

typedef ActorComponent* (*pfunc)(nlohmann::basic_json<>& component);

class ActorFactory {
public:

	ActorFactory();
	SDL_Renderer* renderHandle;
	Actor CreateActorFromFile(std::string filepath);

private:

	std::map<std::string, 
			 std::function<std::shared_ptr<ActorComponent>(nlohmann::basic_json<>&)>>
			 componentCreatorMap;

	void PopulateComponents(std::string filepath, Actor& actor);

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