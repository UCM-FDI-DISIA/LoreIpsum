#include "pch.h"
#include "NetGame.h"

#include "../../gamestates/GameState.h"

#include "../../MultiplayerNamespaces.h"
#include "../../../sdlutils/SDLNetUtils.h"

#include "../managers/MatchManager.h"
#include "../managers/BoardManager.h"
#include "../DeckComponent.h"
#include "../HandComponent.h"
#include "../Card.h"

#include "../DropDetector.h"
#include "../basics/Transform.h"
#include "../managers/CardStateManager.h"
#include "../Cell.h"

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

			auto result =  SDLNetUtils::receiveMsg(rival);

			msg.deserialize(result.buffer);

			switch (msg._type)
			{
			case NetMsgs::_NONE_:	
				TuVieja("Mensaje : _NONE_, RECIBIDO");

				//procesar el mensaje/ lanzar error
				break;
			case NetMsgs::_CHANGE_TURN_:
				TuVieja("Mensaje : CHANGE_TURN, RECIBIDO");

				//procesar el mensaje
				processNextTurn();

				break;
			case NetMsgs::_DRAW_CARD_:
				TuVieja("Mensaje : _DRAW_CARD_, RECIBIDO");

				//procesar el mensaje

				processDrawCard();

				break;
			case NetMsgs::_PLAY_CARD_: {

				TuVieja("Mensaje : _PLAY_CARD_, RECIBIDO");

				//procesar el mensaje

				NetMsgs::PlayCard playMsg;
				playMsg.deserialize(result.buffer);

				processPlayCard(playMsg.index, Vector2D(playMsg.posX, playMsg.posY));

				break;
			}
			case NetMsgs::_END_GAME_:
				TuVieja("Mensaje : _END_GAME_, RECIBIDO");

				//procesar el mensaje

				break;
			case NetMsgs::_FIRST_TURN_OWNER_: {

				TuVieja("Mensaje : _FIRST_TURN_OWNER_, RECIBIDO");

				//procesar el mensaje

				NetMsgs::FirstTurn firstMsg;

				firstMsg.deserialize(result.buffer);

				matchManager->setActualState((Turns::State)firstMsg.myMultiplayerTurn);

				break;
			}
			default:
				break;
			}

	
		}

	}

}

void NetGame::setMatchManager(MatchManager* matchM)
{
	matchManager = matchM;


	//si no somos el host,return 
	if (!GameStateMachine::instance()->getCurrentState()->getIsHost()) return;

	//si sí somos el host
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

void NetGame::setPlayerHand(HandComponent* playerH)
{
	playerHandCmp = playerH;
}

void NetGame::drawCard()
{
	NetMsgs::Msg msg(NetMsgs::_DRAW_CARD_);

	SDLNetUtils::serializedSend(msg, rival);
}

void NetGame::playCard(ecs::entity_t e, Vector2D pos)
{

	int index = playerHandCmp->indexOf(e);

	if (index == -1) {
		//lanzar error
	}
	else {

		NetMsgs::PlayCard msg(index,pos);

		SDLNetUtils::serializedSend(msg, rival);
	}


}

void NetGame::nextTurn()
{
	NetMsgs::Msg msg(NetMsgs::_CHANGE_TURN_);

	SDLNetUtils::serializedSend(msg, rival);

	TuVieja("Envio de mensaje next Tunrn");

}



void NetGame::processDrawCard()
{
	rivalHandCmp->addCard(rivalDeckCmp->drawCard()->getEntity());
}

void NetGame::processPlayCard(int i, Vector2D pos)
{
	Card* card = rivalHandCmp->getHand()[i];

	//dropDetector ocupado
	const auto dropDet = boardManager->getCell(pos.getX(), pos.getY())->getEntity()->getComponent<DropDetector>();
	dropDet->setOcuped(true);

	//colocar la carta en el tablero
	card->getEntity()->getComponent<Transform>()->setGlobalPos(dropDet->getCardPos());
	card->getEntity()->getComponent<CardStateManager>()->putOnBoard();

	//comunicacion con el boardManager
	const Players::Owner playerTurn = mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->getPlayerTurn();
	boardManager->setCard(pos.getX(), pos.getY(), card, playerTurn);
	
}

void NetGame::processNextTurn()
{
	auto turn =  matchManager->getPlayerTurn();
	matchManager->setActualState(turn == Players::PLAYER1 ? Turns::J2_MULTIPLAYER : Turns::J1);
}
