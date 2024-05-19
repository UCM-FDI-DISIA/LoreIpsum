#include "..\pchs\pch.h"
#include "CaseManager.h"

CaseManager::CaseManager() :
	npc_(),
	accepted_(false),
	npcCounter_(),
	initialNpc_(),
	case_(1)
{
}

CaseManager::~CaseManager()
{

}

void CaseManager::update()
{
}

void CaseManager::init()
{
	npcCounter_ = GameStateMachine::instance()->getCurrentState()->getCurrentCase() + 2;

	if (GameStateMachine::instance()->getCurrentState()->getCurrentCase() == 1)
		initialNpc_ = 9;
	else if (GameStateMachine::instance()->getCurrentState()->getCurrentCase() == 2)
		initialNpc_ = 12;
	else if (GameStateMachine::instance()->getCurrentState()->getCurrentCase() == 3)
		initialNpc_ = 16;
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
	initialNpc_ += npcCounter_;
	npcCounter_++;
	accepted_ = false;
	GameStateMachine::instance()->getCurrentState()->nextCase();
	++case_;
}

ecs::entity_t CaseManager::caseNPC()
{
	return npc_;
}
