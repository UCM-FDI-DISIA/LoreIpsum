#pragma once

//Checkml
#include <game/checkML.h>

#include "Component.h"

class ComponentUpdate : public ecs::Component {

public:
	ComponentUpdate() : Component() {}

	virtual ~ComponentUpdate() {};

	// Para actualizar el estado
	virtual void update() {};
};

