#pragma once
#include "../pch.h"



class NPCFactory
{
public:
	NPCFactory() {};
	virtual ~NPCFactory() {};

	virtual ecs::entity_t createNPC(JsonData::NPCData info, ecs::entity_t parent) = 0;

};

