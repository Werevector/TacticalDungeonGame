#pragma once
#include <string>

class ActorComponent {

	friend class ActorFactory;

public:

	ActorComponent();
	~ActorComponent();

	unsigned int GetComponentId() { return component_id; }
	virtual void Update(int framedelta) {};
	std::string GetComponentName() { return component_name; }

protected:
	unsigned int component_id;
	unsigned int owner_id;
	std::string component_name;

private:

	void setOwner(unsigned int id) {
		owner_id = id;
	}

};