#include <../pchs/pch.h>
#include "EndGameState.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ImageWithFrames.h"


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
	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onSkip(); });

	// creditos
	auto eCin = Instantiate(Vector2D());

	auto eCinTr = eCin->addComponent<Transform>();
	eCinTr->setGlobalPos(0, 0);
	eCinTr->setGlobalScale(1, 1);
	auto eCinSr = eCin->addComponent<SpriteRenderer>("credits");
	auto eCinIwf = eCin->addComponent<ImageWithFrames>(eCinSr, 12, 13, 1);

	eCinIwf->addCallback([this]
		{
			GameStateMachine::instance()->setState(GameStates::LOGOSTATE, true, true);
		});
}

void EndGameState::onExit()
{
	// se desuscribe al evento de click izq
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onSkip(); });

	GameStateMachine::instance()->getMngr()->Free();
}

void EndGameState::onSkip()
{
	GameStateMachine::instance()->setState(GameStates::LOGOSTATE, true, true);
}