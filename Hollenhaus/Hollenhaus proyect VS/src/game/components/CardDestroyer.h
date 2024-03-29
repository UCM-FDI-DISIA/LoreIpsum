#pragma once
#include "ComponentUpdate.h"

class CardDestroyer : public ComponentUpdate
{
private:
	ecs::entity_t obj;
public:
	CardDestroyer();
	~CardDestroyer();

	void initComponent() override;

	void destroyCard();
};

