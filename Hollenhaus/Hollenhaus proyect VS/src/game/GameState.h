#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include "ecs.h"

/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>
class Game;
class GameState {

protected:

	//A lo mejor deja de hacer falta
	Game* game;			//Puntero al juego

public:
	GameState() = default;
	virtual ~GameState();		//Destructora

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //update de las entidades
	virtual void render() const; // render de las entidades

};

#endif // !GameState_H_

