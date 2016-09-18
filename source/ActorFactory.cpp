#include "ActorFactory.h"


ActorFactory::ActorFactory()
{
	auto IsoSpriteRenderComponentCreator = [=](nlohmann::basic_json<>& component)
	{
		IsoSpriteRenderComponent isr(renderHandle);
		
		std::string imageName = component.find("spritesheet").value();
		std::string imageType = component.find("imagetype").value();
		isr.SetSpriteSheetName(imageName, imageType);
		
		auto target = component.find("position");
		if (target != component.end())
		{
			int x = target.value()["X"];
			int y = target.value()["Y"];
			isr.SetPos(x, y);
		}
		

		auto keyNode = component.find("key");
		if (keyNode != component.end()) {
			isr.SetKey(keyNode.value());
		}
		
		isr.SetCamera(cameraPtr);
		std::shared_ptr<ActorComponent> isrPointer = std::make_shared<IsoSpriteRenderComponent>(isr);
		return isrPointer;
	};
	componentCreatorMap.emplace("IsoSpriteRenderComponent", IsoSpriteRenderComponentCreator);

	auto MovementComponentCreator = [=](nlohmann::basic_json<>& component)
	{
		MovementComponent mcc;

		auto positionAttr = component.find("position");
		if (positionAttr != component.end()) 
		{
			float x = positionAttr.value()["X"];
			float y = positionAttr.value()["Y"];
			mcc.SetPos(x, y);
		}

		auto velocityAttr = component.find("velocity");
		if (velocityAttr != component.end())
		{
			float x = velocityAttr.value()["X"];
			float y = velocityAttr.value()["Y"];
			mcc.SetVelocity(x, y);
		}

		auto accelerationAttr = component.find("acceleration");
		if (accelerationAttr != component.end())
		{
			float x = accelerationAttr.value()["X"];
			float y = accelerationAttr.value()["Y"];
			mcc.SetAcceleration(x, y);
		}
		std::shared_ptr<ActorComponent> mccPointer = std::make_shared<MovementComponent>(mcc);
		return mccPointer;
	};
	componentCreatorMap.emplace("MovementComponent", MovementComponentCreator);

	auto MouseClickControlComponentCreator = [=](nlohmann::basic_json<>& JSONcomponent)
	{
		MouseClickControlComponent component;
		component.SetCamera(cameraPtr);
		component.mGameMapPtr = mGameMapPtr;
		std::shared_ptr<ActorComponent> componentPointer = std::make_shared<MouseClickControlComponent>(component);
		return componentPointer;
	};
	componentCreatorMap.emplace("MouseClickControlComponent", MouseClickControlComponentCreator);
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
