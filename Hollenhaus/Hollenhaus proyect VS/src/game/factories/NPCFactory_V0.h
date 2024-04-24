#pragma once
#include <../pchs/pch.h>

#include "NPCFactory.h"


class NPCFactory_V0 : public NPCFactory
{
public:
	NPCFactory_V0() : NPCFactory()
	{
	};

	~NPCFactory_V0() override
	{
	};

	ecs::entity_t createNPC(JsonData::NPCData info, ecs::entity_t parent) override;
};
