#include "pch.h"
#include "TutorialManager.h"

TutorialManager::TutorialManager() : ended(false)
{


}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::initComponent()
{

	resetAction();
}

void TutorialManager::update()
{
}

void TutorialManager::actionEnded()
{
	ended = true;

}

void TutorialManager::resetAction()
{
	ended = false;
}
