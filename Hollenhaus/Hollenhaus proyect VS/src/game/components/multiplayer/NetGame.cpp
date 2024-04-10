#include "pch.h"
#include "NetGame.h"

#include "../../gamestates/GameState.h"


NetGame::NetGame()
{
	rival = GameStateMachine::instance()->getCurrentState()->getSocketRival();
}

NetGame::~NetGame()
{
}

void NetGame::initComponent()
{
}

void NetGame::update()
{
}
