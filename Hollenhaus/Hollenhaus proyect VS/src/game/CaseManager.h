#pragma once

#include <../pchs/pch.h>

class CaseManager : ComponentUpdate
{
public:
	CaseManager();
	~CaseManager() = default;

	void initComponent() override;
	void update() override;

	ecs::entity_t caseNPC();
	void addNPC(ecs::entity_t npc);

private:
	ecs::entity_t npc_;

	bool accepted_;
};

