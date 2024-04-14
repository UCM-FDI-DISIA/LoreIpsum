#include "pch.h"
#include "NetGame.h"

#include "../../gamestates/GameState.h"

#include "../../MultiplayerNamespaces.h"
#include "../../../sdlutils/SDLNetUtils.h"



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

void NetGame::setMatchManager(MatchManager* matchM)
{
	matchManager = matchM;
}

void NetGame::setBoardManager(BoardManager* boardM)
{
	boardManager = boardM;
}

void NetGame::setRivalHand(HandComponent* rivalH)
{
	rivalHandCmp = rivalH;
}

void NetGame::setRivalDeck(DeckComponent* rivalD)
{
	rivalDeckCmp = rivalD;
}

void NetGame::drawCard()
{
}

void NetGame::playCard(int i, Vector2D pos)
{
}

void NetGame::nextTurn()
{
	NetMsgs::Msg msg(NetMsgs::_CHANGE_TURN_);

	SDLNetUtils::serializedSend(msg, rival);
}
