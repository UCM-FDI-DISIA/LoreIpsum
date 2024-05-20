#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ImageWithFrames.h"
#include "../components/basics/Transform.h"
#include "CinematicOutroState.h"

CinematicOutroState::CinematicOutroState()
{
}

CinematicOutroState::~CinematicOutroState()
{
}

void CinematicOutroState::refresh()
{
}

void CinematicOutroState::update()
{
	GameState::update();
}

void CinematicOutroState::render() const
{
	GameState::render();
}

void CinematicOutroState::onEnter()
{
	TuVieja("\nEnter CinematicOutroState");
	auto eCin = Instantiate(Vector2D());

	auto eCinTr = eCin->addComponent<Transform>();
	eCinTr->setGlobalPos(0, 0);
	eCinTr->setGlobalScale(2, 2);
	auto eCinSr = eCin->addComponent<SpriteRenderer>("outro");
	auto eCinIwf = eCin->addComponent<ImageWithFrames>(eCinSr, 18, 22, 1, 120);

	eCinIwf->addCallback([this]
		{
			GameStateMachine::instance()->setState(GameStates::ENDGAME, true, true);
		});
}

void CinematicOutroState::onExit()
{
	TuVieja("\nExit CinematicOutroState");

	GameStateMachine::instance()->getMngr()->Free();
}
