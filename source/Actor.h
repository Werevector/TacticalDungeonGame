#pragma once
#include <map>
#include "ActorComponent.h"
#include "json.hpp"


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

	

private:
	
	unsigned int actor_id;
	bool AddActorComponent(std::shared_ptr<ActorComponent> component);
	std::map<std::string, std::shared_ptr<ActorComponent>> component_map;


};