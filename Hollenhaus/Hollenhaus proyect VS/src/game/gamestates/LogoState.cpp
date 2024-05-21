#include "..\pchs\pch.h"
#include "LogoState.h"

LogoState::LogoState() :
	logo_(),
	time_(3000),
	currentTime_()
{
}

void LogoState::update()
{
	if (sdlutils().currRealTime() > currentTime_ + time_)
	{
		GameStateMachine::instance()->setState(GameStates::MAINMENU, true, true);
	}
}

void LogoState::render() const
{
	GameState::render();
}

void LogoState::refresh()
{
	GameState::refresh();
}

void LogoState::onEnter()
{
	currentTime_ = sdlutils().currRealTime();
	logo_ = Instantiate(Vector2D((sdlutils().width() / 2) - 120, (sdlutils().height() / 2) - 160));
	logo_->addComponent<SpriteRenderer>("nosotros");
}

void LogoState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();
}
