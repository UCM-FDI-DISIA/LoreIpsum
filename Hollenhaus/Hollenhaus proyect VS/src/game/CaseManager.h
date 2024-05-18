#pragma once

#include <../pchs/pch.h>

class CaseManager 
{
public:
	CaseManager();
	~CaseManager();

	void update();
	void init();

	// NPC
	ecs::entity_t caseNPC();
	void addNPC(ecs::entity_t npc);

	// Caso
	bool accepted();
	void accept();
	void resetCase();
	int npc_n() { return npcCounter_; }
	int npcBegin() { return initialNpc_; }
private:
	ecs::entity_t npc_;

	bool accepted_;
	int npcCounter_;
	int initialNpc_;
};

