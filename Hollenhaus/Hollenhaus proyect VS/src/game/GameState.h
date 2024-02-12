#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include <list>
#include <string>
//poli: hola estoy usando los apuntes del t5 de tpv1 para esto uwu 

class GameState {

protected:


public:

	GameState(){};

	virtual ~GameState() {};
	
	virtual void Render() const;
	virtual void Update();

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;

};



#endif // !GameState_H_

