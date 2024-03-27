#pragma once
#include "../pch.h"
#include "NPCFactory.h"


class NPCFactory_V0 : public NPCFactory {
public:
	NPCFactory_V0() {};
	~NPCFactory_V0() {};

	ecs::entity_t createNPC(std::string id, std::string sprite,
		Vector2D scale, Vector2D pos, int type, int scene, int layer,
		ecs::entity_t parent) override;
};
