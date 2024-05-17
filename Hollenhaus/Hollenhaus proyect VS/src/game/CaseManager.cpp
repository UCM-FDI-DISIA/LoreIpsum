#include "..\pchs\pch.h"
#include "CaseManager.h"

CaseManager::CaseManager() :
	npc_(),
	accepted_(false)
{
}

CaseManager::~CaseManager()
{

}

void CaseManager::update()
{
}

void CaseManager::addNPC(ecs::entity_t npc)
{
	npc_ = npc;
}

bool CaseManager::accepted()
{
	return accepted_;
}

void CaseManager::accept()
{
	accepted_ = true;
}

void CaseManager::resetCase()
{
	accepted_ = false;
	GameStateMachine::instance()->getCurrentState()->nextCase();
}

ecs::entity_t CaseManager::caseNPC()
{
	return npc_;
}
