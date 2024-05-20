#include <../pchs/pch.h>
#include "EndGameState.h"


EndGameState::EndGameState()
{
}

EndGameState::~EndGameState()
{
}

void EndGameState::update()
{
	GameState::update();
}

void EndGameState::render() const
{
	GameState::render();
}

void EndGameState::refresh()
{
	GameState::refresh();
}

void EndGameState::onEnter()
{
	std::cout << "\nENTER ENDGAME.\n";
	// creditos
	/*auto eCin = Instantiate(Vector2D());

	auto eCinTr = eCin->addComponent<Transform>();
	eCinTr->setGlobalPos(0, 0);
	eCinTr->setGlobalScale(0.5f, 0.5f);
	auto eCinSr = eCin->addComponent<SpriteRenderer>("transicion_puerta");
	auto eCinIwf = eCin->addComponent<ImageWithFrames>(eCinSr, 1, 10, 1);

	eCinIwf->addCallback([this]
		{
		});*/
	GameStateMachine::instance()->setState(GameStates::MAINMENU, true, true);
}

void EndGameState::onExit()
{
	std::cout << "\nEXIT ENDGAME.\n";
	GameStateMachine::instance()->getMngr()->Free();
}
