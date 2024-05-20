#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ImageWithFrames.h"
#include "../components/basics/Transform.h"
#include "CinematicOutroState.h"
#include "../SoundManager.h"


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
	// llamada al input
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onSkip(); });

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


	/// MUSICA
	auto music = SoundManager::instance();
	music->startSoundEffect(Sounds::SOUND_EFFECTS::CANDLE_SE, -1);
}

void CinematicOutroState::onExit()
{
	TuVieja("\nExit CinematicOutroState");

	// se desuscribe al evento de click izq
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { onSkip(); });

	auto music = SoundManager::instance();
	music->stopSoundEffect(Sounds::SOUND_EFFECTS::CANDLE_SE);

	GameStateMachine::instance()->getMngr()->Free();
}

void CinematicOutroState::onSkip()
{
	GameStateMachine::instance()->setState(GameStates::ENDGAME, true, true);
}