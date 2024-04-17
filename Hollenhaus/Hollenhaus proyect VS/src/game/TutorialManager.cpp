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

	count = 0;
	cooldown = 10;

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

void TutorialManager::wait()
{
	// tiempo de espera
	if (count < cooldown) {

		count++;
	}
	else {
		
		//
		//

		//
		count = 0;
	}
}
