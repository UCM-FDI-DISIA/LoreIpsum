#pragma once

#include "Component.h"
class ComponentRender : public ecs::Component {

public:
	ComponentRender() : Component() {}

	virtual ~ComponentRender() {}


	// Para renderizar el estado
	virtual void render() const {};
};