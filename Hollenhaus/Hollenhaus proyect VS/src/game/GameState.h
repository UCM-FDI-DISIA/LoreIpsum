#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"
#include "Entity.h"

#include <SDL.h>
#include <iostream>
#include <list>
#include <string>
//poli: hola estoy usando los apuntes designpatterns.ecs.ver1 de tpv2 uwu
/// <summary>
/// Clase GameState (o Manager) vista en clase
/// </summary>

class GameState {

protected:
	std::vector<Entity*> ents_; //vector de entidades de cada estado

public:

	GameState();
	virtual ~GameState();
	
	Entity* addEntity(); //entidades en cada estado
	virtual void refresh(); //borra entidades no vivas
	virtual void update(); //
	virtual void render();



};

#endif // !GameState_H_

