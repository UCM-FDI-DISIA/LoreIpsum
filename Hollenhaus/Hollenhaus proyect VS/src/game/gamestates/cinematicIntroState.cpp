#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ImageWithFrames.h"
#include "../components/basics/Transform.h"
#include "cinematicIntroState.h"
#include "../SoundManager.h"


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
	eCinTr->setGlobalScale(2, 2);
	auto eCinSr = eCin->addComponent<SpriteRenderer>("intro");
	auto eCinIwf = eCin->addComponent<ImageWithFrames>(eCinSr, 33, 34, 1, 120);

	eCinIwf->addCallback([this]
		{
			GameStateMachine::instance()->setState(GameStates::TUTORIAL_OFFICE, true, true);
		});


	/// MUSICA
	auto music = SoundManager::instance();
	music->startSoundEffect(Sounds::SOUND_EFFECTS::AMBIENCE_OFFICE_SE, -1);
}

void CinematicIntroState::onExit()
{
	TuVieja("\nExit CinematicIntroState");


	auto music = SoundManager::instance();
	music->stopSoundEffect(Sounds::SOUND_EFFECTS::AMBIENCE_OFFICE_SE);

	GameStateMachine::instance()->getMngr()->Free();
}
