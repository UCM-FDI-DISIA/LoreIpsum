#pragma once

#include "../ComponentUpdate.h"

#include <SDL_net.h>
#include "../../../utils/Vector2D.h"


/*
Esta clase gestiona el envio y el procesamiento de mensajes en el estado MultiplayerEndGame
Tiene unas funciones que se deben llamar cuando se pulsan los botones correspondiente
Desde fuera hay que suscribir las funciones a su boton correspondiente

El procesamiento de acciones depende del estado en el que
se encuentren ambos jugadores(en relacion a los botones que hayan seleccionado)
*/

class NetEndGame 
	: public ComponentUpdate
{
public:
	//constructora y destructora
	NetEndGame();
	~NetEndGame();

	void initComponent() override;
	void update() override;

	//Metodos que envian mensajes(deben estar suscritos a los botones del estado)
	void playAgain();
	void changeMaze();
	void exit();

	//getters del estado de los botones(si estan seleccionados o no)
	bool getPlayAgainSelected();
	bool getChangeMazeSelected();

private:

	//el jugador contra el que estamos jugando
	TCPsocket rival = nullptr;
	SDLNet_SocketSet socketSet; //para recibir los mensajes con comunicacion NO-Bloqueante

	//booleanos para saber el estado de los botones de ambos jugadores
	bool changeMazeSelected = false;
	bool playAgainSelected = false;

	bool rivalChangeMazeSelected = false;
	bool rivalPlayAgainSelected = false;
};

