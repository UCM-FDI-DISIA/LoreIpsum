#include "..\pchs\pch.h"
#include "CaseManager.h"

CaseManager::CaseManager() :
	npc_(nullptr),
	accepted_()
{
}

void CaseManager::initComponent()
{
}

void CaseManager::update()
{
}

void CaseManager::addNPC(ecs::entity_t npc)
{
	npc_ = npc;
}

ecs::entity_t CaseManager::caseNPC()
{
	return npc_;
}
