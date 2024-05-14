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

void CaseManager::setAccepted(bool b)
{
	accepted_ = b;
}

ecs::entity_t CaseManager::caseNPC()
{
	return npc_;
}
