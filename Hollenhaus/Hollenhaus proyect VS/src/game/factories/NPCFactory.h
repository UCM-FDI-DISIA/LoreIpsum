#pragma once

//Checkml
#include <game/checkML.h>




class NPCFactory
{
public:
	NPCFactory() {};
	virtual ~NPCFactory() {};

	virtual ecs::entity_t createNPC(JsonData::NPCData info, ecs::entity_t parent, int convo) = 0;

};

