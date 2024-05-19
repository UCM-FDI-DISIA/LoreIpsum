#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ImageWithFrames.h"
#include "../components/basics/Transform.h"
#include "cinematicIntroState.h"

CinematicIntroState::CinematicIntroState()
{
}

CinematicIntroState::~CinematicIntroState()
{
}

void CinematicIntroState::refresh()
{
}

void CinematicIntroState::update()
{
	GameState::update();
}

void CinematicIntroState::render() const
{
	GameState::render();
}

void CinematicIntroState::onEnter()
{
	TuVieja("\nEnter CinematicIntroState");
	auto eCin = Instantiate(Vector2D());

	auto eCinTr = eCin->addComponent<Transform>();
	eCinTr->setGlobalPos(0, 0);
	eCinTr->setGlobalScale(0.5f, 0.5f);
	auto eCinSr = eCin->addComponent<SpriteRenderer>("transicion_puerta");
	auto eCinIwf = eCin->addComponent<ImageWithFrames>(eCinSr, 1, 10, 1);

	eCinIwf->addCallback([this]
		{
			GameStateMachine::instance()->setState(GameStates::TUTORIAL_OFFICE, true, true);
		});
}

void CinematicIntroState::onExit()
{
	TuVieja("\nExit CinematicIntroState");

	GameStateMachine::instance()->getMngr()->Free();
}
