#pragma once

#include <../pchs/pch.h>

class CaseManager 
{
public:
	CaseManager();
	~CaseManager();

	void update();

	// NPC
	ecs::entity_t caseNPC();
	void addNPC(ecs::entity_t npc);

	// Caso
	bool accepted();
	void setAccepted(bool b);

private:
	ecs::entity_t npc_;

	bool accepted_;

};
