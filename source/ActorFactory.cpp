#include "ActorFactory.h"

ActorFactory::ActorFactory()
{
	auto PrimitiveRendererCreator = [=](nlohmann::basic_json<>& component)
	{
		SDL_Renderer* r = renderHandle;

		SDL_Color c;
		auto color = component.find("color").value();
		c.r = color["R"];
		c.g = color["G"];
		c.b = color["B"];

		SDL_Rect t;
		auto target = component["target"];
		t.x = target["X"];
		t.y = target["Y"];
		t.w = target["W"];
		t.h = target["H"];

		PrimitiveRenderComponent prc(r, c, t);
		std::shared_ptr<ActorComponent> prcPointer = std::make_shared<PrimitiveRenderComponent>(prc);
		return prcPointer;
	};

	componentCreatorMap.emplace("PrimitiveRenderComponent", PrimitiveRendererCreator);
}

Actor ActorFactory::CreateActorFromFile(std::string filepath)
{
	Actor actor(getNextActorId());
	PopulateComponents(filepath, actor);

	return actor;
}

void ActorFactory::PopulateComponents(std::string filepath, Actor& actor)
{
	using nlohmann::json;

	std::ifstream actorstream(filepath);
	
	if (!actorstream.is_open())
	{
		std::cout << "Could not open file: \n" << filepath;
		return;
	}
	else 
	{
		json actorJSON(actorstream);
		auto componentsJSON = actorJSON.find("components").value();
		for (auto& componentJSON : componentsJSON) {
			std::string type = componentJSON.find("component_type").value();
			std::shared_ptr<ActorComponent> newComponentPtr = componentCreatorMap.find(type)->second(componentJSON);
			newComponentPtr->component_name = type;
			newComponentPtr->component_id = getNextComponentId();
			actor.AddActorComponent(newComponentPtr);
		}
	}




}
