#include "ActorFactory.h"
#include "IsometricSpriteRenderer.h"
#include "MovementComponent.h"
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

	auto MovementComponentCreator = [=](nlohmann::basic_json<>& component)
	{
		MovementComponent mcc;

		auto positionAttr = component.find("position");
		if (positionAttr != component.end()) 
		{
			int x = positionAttr.value()["X"];
			int y = positionAttr.value()["Y"];
			mcc.SetPos(x, y);
		}

		auto velocityAttr = component.find("velocity");
		if (velocityAttr != component.end())
		{
			int x = velocityAttr.value()["X"];
			int y = velocityAttr.value()["Y"];
			mcc.SetVelocity(x, y);
		}

		auto accelerationAttr = component.find("acceleration");
		if (accelerationAttr != component.end())
		{
			int x = accelerationAttr.value()["X"];
			int y = accelerationAttr.value()["Y"];
			mcc.SetAcceleration(x, y);
		}

		std::shared_ptr<ActorComponent> mccPointer = std::make_shared<MovementComponent>(mcc);
		return mccPointer;
	};
	componentCreatorMap.emplace("MovementComponent", MovementComponentCreator);
}

std::shared_ptr<Actor> ActorFactory::CreateActorFromFile(std::string filepath)
{
	Actor actor(getNextActorId());
	std::shared_ptr<Actor> actorPtr = std::make_shared<Actor>(actor);
	PopulateComponents(filepath, actorPtr);

	return actorPtr;
}

void ActorFactory::PopulateComponents(std::string filepath, std::shared_ptr<Actor> actorStrongPtr)
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
			newComponentPtr->setOwner(actorStrongPtr->GetActorId(), actorStrongPtr);
			actorStrongPtr->AddActorComponent(newComponentPtr);
		}
	}




}
