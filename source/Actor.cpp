#include "Actor.h"

Actor::Actor(unsigned int id)
{
	actor_id = id;
}

Actor::~Actor()
{

}

void Actor::Destroy()
{
	component_map.clear();
}

void Actor::Update(int framedelta)
{
	for (auto& component : component_map) {
		component.second->Update(framedelta);
	}
}

std::shared_ptr<ActorComponent> Actor::FindComponent(std::string name)
{
	std::shared_ptr<ActorComponent> component = component_map.find(name)->second;
	return component;
}

bool Actor::AddActorComponent(std::shared_ptr<ActorComponent> component) {

	component_map.emplace(component->GetComponentName(), component);

	return 1;
}
