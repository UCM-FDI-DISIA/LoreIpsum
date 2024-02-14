#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"
#include "Entity.h"

#include <SDL.h>
#include <iostream>
#include <list>
#include <string>
//poli: hola estoy usando los apuntes del t5 de tpv1 para esto uwu 

class GameState {

protected:
	std::vector<Entity*> ents_; //vector de entidades de cada estado

public:

	GameState();
	virtual ~GameState();
	
	Entity* addEntity(); //entidades en cada estado
	void refresh(); //borra entidades no vivas
	void update(); //
	void render();
};

#endif // !GameState_H_

