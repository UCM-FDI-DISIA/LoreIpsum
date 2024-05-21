#include "..\pchs\pch.h"
#include "CaseManager.h"

CaseManager::CaseManager() :
	npc_(),
	accepted_(false),
	initialNpc_(9),
	case_(1)
{
	npcCounter_ = case_ + 2;
}

CaseManager::~CaseManager()
{

}

void CaseManager::update()
{
}

void CaseManager::init()
{
	case_ = GameStateMachine::instance()->getCurrentState()->getCurrentCase();
	accepted_ = GameStateMachine::instance()->getCurrentState()->getAccepted();

	npcCounter_ = case_ + 2;

	if (case_ == 1)
		initialNpc_ = 9;
	else if (case_ == 2)
		initialNpc_ = 12;
	else if (case_ == 3)
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
	GameStateMachine::instance()->getCurrentState()->setAccepted(accepted_);
}

void CaseManager::resetCase()
{
	initialNpc_ += npcCounter_;
	npcCounter_++;
	accepted_ = false;
	GameStateMachine::instance()->getCurrentState()->setAccepted(accepted_);
	GameStateMachine::instance()->getCurrentState()->nextCase();
	GameStateMachine::instance()->getCurrentState()->resetShop();
	++case_;
}

ecs::entity_t CaseManager::caseNPC()
{
	return npc_;
}
