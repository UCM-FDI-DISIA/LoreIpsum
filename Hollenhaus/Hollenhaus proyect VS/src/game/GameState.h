#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include <list>
#include <string>

#include "Entity.h"

/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>
class GameState {

protected:


public:

	GameState();
	virtual ~GameState();

	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //
	virtual void render();
};

#endif // !GameState_H_

