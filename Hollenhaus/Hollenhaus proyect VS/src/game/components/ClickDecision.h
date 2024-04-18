#pragma once
#include "ComponentUpdate.h"

#include "managers/Manager.h"
#include "basics/BoxCollider.h"

class ClickDecision :
	public ComponentUpdate
{
public:
	ClickDecision(int decision, ecs::entity_t parent, int scene);

	~ClickDecision() override
	{
	}

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
	void OnLeftClickUp();

	void TakeDecision();

private:
	ecs::entity_t parent_;
	int scene_;

	int decision_;
	bool click_;

	BoxCollider* collider_;
};
