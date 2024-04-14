#include "pch.h"
#include "TutorialBoardState.h"

TutorialBoardState::TutorialBoardState()
{
	TuVieja("Loading Tutorial Board");
}

TutorialBoardState::~TutorialBoardState()
{

}

void TutorialBoardState::refresh()
{
	GameState::refresh();
}

void TutorialBoardState::update()
{
	GameState::update();

	updateTutorialState();
}

void TutorialBoardState::render() const
{
	GameState::render();
}

void TutorialBoardState::onEnter()
{


}

void TutorialBoardState::onExit()
{


}

void TutorialBoardState::updateTutorialState()
{
	if (currentState != nextState) {
		switch (nextState)
		{
		case INIT:
			break;
		case CARD:
			break;
		default:
			break;
		}

		currentState = nextState;
	}
}

void TutorialBoardState::nextTutorialState()
{
	nextState++;
}

void TutorialBoardState::createPopUp()
{


}