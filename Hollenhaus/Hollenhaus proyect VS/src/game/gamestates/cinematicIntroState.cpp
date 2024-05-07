#include <../pchs/pch.h>
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "cinematicIntroState.h"
#include "../Data.h"

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
}

void CinematicIntroState::render() const
{
}

void CinematicIntroState::onEnter()
{
	data->resetSave();
}

void CinematicIntroState::onExit()
{
}
