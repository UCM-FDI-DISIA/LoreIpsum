#pragma once

#include "../ComponentUpdate.h"

#include <SDL_net.h>
#include "../../../utils/Vector2D.h"

class NetEndGame 
	: public ComponentUpdate
{
public:
	//constructora y destructora
	NetEndGame();
	~NetEndGame();

	void initComponent() override;
	void update() override;


	void playAgain();
	void changeMaze();
	void exit();

private:

	//el jugador contra el que estamos jugando
	TCPsocket rival;
	SDLNet_SocketSet socketSet; //para recibir los mensajes con comunicacion NO-Bloqueante





};

