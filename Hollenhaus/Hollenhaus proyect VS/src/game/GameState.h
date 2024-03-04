#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include "ecs.h"
#include "Data.h"

/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>
class Game;
class GameState {

protected:

	static Data* data; // puntero a la data

	//A lo mejor deja de hacer falta
	//Game* game;			//Puntero al juego

public:
	//LAS ENTIDADES ¡NO! SE CREAN EN LA CONSTRUCTORA SE CREAN EN EL ONENTER Y SE ELIMINAN EN EL ONEXIT 
	GameState() {};
	virtual ~GameState();		//Destructora

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //update de las entidades
	virtual void render() const; // render de las entidades

	//Para testeo de estrada y salida de estados
	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	// ---- setters ----
	// settea la data
	static void setData(Data* _data) { data = _data; }
};

#endif // !GameState_H_