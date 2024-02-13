#pragma once

#include "Component.h"

class ComponentUpdate : public Component {

public:
	ComponentUpdate() : Component() {}

	virtual ~ComponentUpdate() {};

	// Para actualizar el estado
	virtual void update() {};
};

