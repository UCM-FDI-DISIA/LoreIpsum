#ifndef EventHandler_H_
#define EventHandler_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

class EventHandler {

public:
	virtual void handleEvent(const SDL_Event& ev) = 0;

};

#endif // !EventHandler_H_