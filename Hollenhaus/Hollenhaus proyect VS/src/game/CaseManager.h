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
	int getCaseShopCardsById(const int i) const { return shopCards_[case_ - 1][i]; }
private:
	ecs::entity_t npc_;

	bool accepted_;
	int npcCounter_;
	int initialNpc_;
	int case_;

	std::vector<std::vector<int>> shopCards_ { {20, 27, 31, 33}, {13, 21, 28, 48}, {44, 45, 46, 47} };
};

