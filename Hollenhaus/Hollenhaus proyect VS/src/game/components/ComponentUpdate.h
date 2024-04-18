#pragma once

#include "Component.h"

class ComponentUpdate : public ecs::Component
{
public:
	ComponentUpdate() : Component()
	{
	}

	~ComponentUpdate() override
	{
	};

	// Para actualizar el estado
	virtual void update()
	{
	};
};
