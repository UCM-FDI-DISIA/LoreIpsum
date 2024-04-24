#pragma once
#include "../ComponentUpdate.h"

#include <SDL_net.h>
#include "../../../utils/Vector2D.h"

//forward declaration 
class BoardManager;
class HandComponent;
class DeckComponent;
class MatchManager;


/*
Esta clase gestiona la comunicacion net del juego en el estado MultiplayerGame, mediante el protocolo TCP
Se encarga de enviar mensajes de las acciones realizadas y de procesar los mensajes de las acciones del otro jugador
Tiene referencias a varios componentes importantes del flujo del juego que se deben settear desde fuera


*/

class NetGame
	:public ComponentUpdate
{
public:
	//constructora y destructora
	NetGame();
	~NetGame();

	void update() override;

	//SETTERS DE REFERENCIAS
	void setMatchManager(MatchManager* matchM);
	void setBoardManager(BoardManager* boardM);

	void setRivalHand(HandComponent* rivalH);
	void setRivalDeck(DeckComponent* rivalD);

	void setPlayerHand(HandComponent* playerH);

	//METODOS QUE ENVIAN LAS ACCIONES AL OTRO JUGADOR

	//envia el mesaje de que se ha robado una carta
	void drawCard();

	//envia el mensaje de que se ha jugado cierta carta en cierta casilla
	//pos es la coordenada X,Y de la casilla del tablero en la que se ha colocado la carta
	void playCard(ecs::entity_t e, Vector2D pos);

	//envia el mensaje de que se ha pulsado el boton de pasar turno
	void nextTurn();

private:

	//el jugador contra el que estamos jugando
	TCPsocket rival;
	SDLNet_SocketSet socketSet; //para recibir los mensajes con comunicacion NO-Bloqueante
	
	//referencias a componentes del juego para realizar acciones
	MatchManager* matchManager;
	BoardManager* boardManager;

	HandComponent* rivalHandCmp;
	DeckComponent* rivalDeckCmp;

	//para saber que carta estamos colocando
	HandComponent* playerHandCmp;


	//METODOS QUE PROCESAN LAS ACCIONES QUE EL OTRO JUGADOR HA REALIZADO
	//(Al procesar la accion, la realizamos en este programa , para sincronizar las acciones de ambos jugadores)

	//procesa que el otro jugador ha robado una carta, roba una carta del mazo del rival
	void processDrawCard();

	//procesa que el otro jugador ha jugado cierta carta en cierta posicion, la juega en este programa
	// i es el indice de la carta en relacion a la mano(del rival)
	//pos es la coordenada X,Y de la casilla del tablero en la que se ha colocado la carta
	void processPlayCard(int i, Vector2D pos);

	//procesa que el otro jugador ha pulsado el boton de cambiar turno, cambia de turno
	void processNextTurn();
};

