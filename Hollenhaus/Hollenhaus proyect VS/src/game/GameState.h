#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include <list>

class GameState {

protected:


public:

	GameState(){};

	virtual ~GameState() {};
	
	virtual void Render() const ;

	virtual void Update();

};



#endif // !GameState_H_

