#pragma once

#include "Component.h"

class ComponentRender : public Component {

public:
	ComponentRender() : Component() {}

	virtual ~ComponentRender() {}

	// Para renderizar el estado
	virtual void render() const {};
};