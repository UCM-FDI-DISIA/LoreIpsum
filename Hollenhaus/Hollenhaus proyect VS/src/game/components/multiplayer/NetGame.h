#pragma once
#include "../ComponentUpdate.h"

#include <SDL_net.h>
#include "../../../utils/Vector2D.h"

class BoardManager;
class HandComponent;
class DeckComponent;
class MatchManager;

class NetGame
	:public ComponentUpdate
{
public:

	NetGame();
	~NetGame();

	void initComponent() override;
	void update() override;

	void setMatchManager(MatchManager* matchM);
	void setBoardManager(BoardManager* boardM);

	void setRivalHand(HandComponent* rivalH);
	void setRivalDeck(DeckComponent* rivalD);

	void drawCard();
	void playCard(int i, Vector2D pos);
	void nextTurn();

private:

	TCPsocket rival;
	SDLNet_SocketSet socketSet;

	MatchManager* matchManager;
	BoardManager* boardManager;

	HandComponent* rivalHandCmp;
	DeckComponent* rivalDeckCmp;

};

