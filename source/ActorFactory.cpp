#include "ActorFactory.h"

ActorFactory::ActorFactory()
{
	auto IsometricSpriteRendererCreator = [=](nlohmann::basic_json<>& component)
	{
		IsometricSpriteRenderer isr(renderHandle);
		
		std::string imageName = component.find("spritesheet").value();
		std::string imageType = component.find("imagetype").value();
		isr.SetSpriteSheetName(imageName, imageType);
		
		auto target = component.find("position");
		int x = target.value()["X"];
		int y = target.value()["Y"];
		isr.SetPos(x, y);

		auto keyNode = component.find("key");
		if (keyNode != component.end()) {
			isr.SetKey(keyNode.value());
		}
		
		std::shared_ptr<ActorComponent> isrPointer = std::make_shared<IsometricSpriteRenderer>(isr);
		return isrPointer;
	};
	componentCreatorMap.emplace("IsometricSpriteRenderer", IsometricSpriteRendererCreator);
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
		
		for (auto& componentJSON : componentsJSON)
		{
			std::string type = componentJSON.find("component_type").value();
			std::shared_ptr<ActorComponent> newComponentPtr = componentCreatorMap.find(type)->second(componentJSON);
			newComponentPtr->component_name = type;
			newComponentPtr->component_id = getNextComponentId();
			newComponentPtr->PostInit();
			newComponentPtr->setOwner(actor.GetActorId());
			actor.AddActorComponent(newComponentPtr);
		}
	}




}
