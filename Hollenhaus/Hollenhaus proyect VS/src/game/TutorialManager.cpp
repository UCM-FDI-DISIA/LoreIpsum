#include "pch.h"
#include "TutorialManager.h"
#include "../game/gamestates/TutorialBoardState.h"

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

	isTutorial = false;

	//data =
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

void TutorialManager::wait(std::function<void()> callback)
{
	// tiempo de espera
	if (count < cooldown) {

		count++;
	}
	else {
		
		//
		callback();

		//
		count = 0;
	}
}

void TutorialManager::tutorialActionEnded(Tutorials::Tutorials t, int i)
{
	if (isTutorial && t == currtut && i == currstate) {

		actionEnded();
	}
}
