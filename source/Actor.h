#pragma once
#include <map>
//#include "ActorComponent.h"
#include "json.hpp"

class Actor;
class ActorComponent {

	friend class ActorFactory;

public:

	ActorComponent() {};
	~ActorComponent() {};
	virtual void Init() {};
	virtual void PostInit() {};

	unsigned int GetComponentId() { return component_id; }
	virtual void Update(int framedelta) {};
	std::string GetComponentName() { return component_name; }

protected:
	unsigned int component_id;
	unsigned int mOwner;
	std::weak_ptr<Actor> ownerPtr;
	std::string component_name;

private:

	void setOwner(unsigned int ownerId, std::weak_ptr<Actor> owner) {
		mOwner = ownerId;
		ownerPtr = owner;
	}

};

class Actor {
	
	friend class ActorFactory;

public:

	Actor(unsigned int id);
	~Actor();
	
	void Destroy();
	void Update(int framedelta);

	unsigned int GetActorId() {
		return actor_id;
	}

	std::shared_ptr<ActorComponent> FindComponent(std::string name);

	

private:
	
	unsigned int actor_id;
	bool AddActorComponent(std::shared_ptr<ActorComponent> component);
	std::map<std::string, std::shared_ptr<ActorComponent>> component_map;


};