#include "pch.h"
#include "NetGame.h"

#include "../../gamestates/GameState.h"

#include "../../MultiplayerNamespaces.h"
#include "../../../sdlutils/SDLNetUtils.h"

#include "../managers/MatchManager.h"



NetGame::NetGame()
{
	rival = GameStateMachine::instance()->getCurrentState()->getSocketRival();



	//creacion del socketSet
	socketSet = SDLNet_AllocSocketSet(1);

	// añadir el socker al sockerSet
	SDLNet_TCP_AddSocket(socketSet, rival);


	

}

NetGame::~NetGame()
{
}

void NetGame::initComponent()
{
}

void NetGame::update()
{
	if (SDLNet_CheckSockets(socketSet, 0) > 0) {

		if (SDLNet_SocketReady(rival)) {

			NetMsgs::Msg msg;

			SDLNetUtils::deserializedReceive(msg, rival);


			//identificar el mensaje
			if (msg._type == NetMsgs::_NONE_) {
				TuVieja("Mensaje : _NONE_, RECIBIDO");

				//procesar el mensaje/ lanzar error

			}
			else if (msg._type == NetMsgs::_CHANGE_TURN_) {
				TuVieja("Mensaje : CHANGE_TURN, RECIBIDO");

				//procesar el mensaje
				processNextTurn();

			}
			else if (msg._type == NetMsgs::_DRAW_CARD_) {
				TuVieja("Mensaje : _DRAW_CARD_, RECIBIDO");

				//procesar el mensaje

			}
			else if (msg._type == NetMsgs::_PLAY_CARD_) {
				TuVieja("Mensaje : _PLAY_CARD_, RECIBIDO");

				//procesar el mensaje
				NetMsgs::PlayCard playMsg;

				SDLNetUtils::deserializedReceive(playMsg, rival);


			}
			else if (msg._type == NetMsgs::_END_GAME_) {
				TuVieja("Mensaje : _END_GAME_, RECIBIDO");

				//procesar el mensaje

			}
			else if (msg._type == NetMsgs::_FIRST_TURN_OWNER_) {
				TuVieja("Mensaje : _FIRST_TURN_OWNER_, RECIBIDO");

				//procesar el mensaje

				NetMsgs::FirstTurn firstMsg;

				SDLNetUtils::deserializedReceive(firstMsg, rival);

				matchManager->setActualState((Turns::State)firstMsg.myMultiplayerTurn);
			}
			
		}

	}

}

void NetGame::setMatchManager(MatchManager* matchM)
{
	matchManager = matchM;


	//si no somos el host
	if (!GameStateMachine::instance()->getCurrentState()->getIsHost()) return;
	//decidir quien saca aleatoriamente

	Turns::State  myTurn;
	Turns::State  rivalTurn;

	if (sdlutils().rand().nextInt(0, 2) == 1) {

		myTurn = Turns::J1;
		rivalTurn = Turns::J2_MULTIPLAYER;
	}
	else {
		myTurn = Turns::J2_MULTIPLAYER;
		rivalTurn = Turns::J1;
	}

	matchManager->setActualState(myTurn);

	NetMsgs::FirstTurn msg(rivalTurn);

	SDLNetUtils::serializedSend(msg, rival);

	TuVieja("Envio del mensaje del primer turno");
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
	NetMsgs::Msg msg(NetMsgs::_DRAW_CARD_);

	SDLNetUtils::serializedSend(msg, rival);
}

void NetGame::playCard(int i, Vector2D pos)
{
	NetMsgs::PlayCard msg(i,pos);

	SDLNetUtils::serializedSend(msg, rival);
}

void NetGame::nextTurn()
{
	NetMsgs::Msg msg(NetMsgs::_CHANGE_TURN_);

	SDLNetUtils::serializedSend(msg, rival);

	TuVieja("Envio de mensaje next Tunrn");

}

void NetGame::processDrawCard()
{
}

void NetGame::processPlayCard(int i, Vector2D pos)
{
}

void NetGame::processNextTurn()
{
	auto turn =  matchManager->getPlayerTurn();
	matchManager->setActualState(turn == Players::PLAYER1 ? Turns::J2_MULTIPLAYER : Turns::J1);
}
