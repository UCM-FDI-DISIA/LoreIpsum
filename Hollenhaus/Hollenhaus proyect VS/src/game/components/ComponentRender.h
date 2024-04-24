#pragma once

#include "Component.h"

class ComponentRender : public ecs::Component
{
public:
	ComponentRender() : Component()
	{
	}

	~ComponentRender() override
	{
	}


	// Para renderizar el estado
	virtual void render() const
	{
	};
};
