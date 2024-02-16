#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include "ecs.h"

/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>
class GameState {

protected:

	ecs::Manager* mngr;

public:

	GameState();
	virtual ~GameState();

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //
	virtual void render();

	void PruebaInput();
};

#endif // !GameState_H_

