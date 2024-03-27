#pragma once
#include "../pch.h"



class NPCFactory
{
public:
	NPCFactory() {};
	virtual ~NPCFactory() {};

	virtual ecs::entity_t createNPC(std::string id, std::string sprite, 
		Vector2D scale, Vector2D pos, int type, int scene, int layer, 
		ecs::entity_t parent) = 0;

};

