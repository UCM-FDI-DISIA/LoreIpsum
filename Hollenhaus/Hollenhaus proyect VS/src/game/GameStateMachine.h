#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include <stack>
#include <functional>

#include "GameState.h"


class GameStateMachine {
	//preguntar: usamos vector de estados o stack? 
	// stack no usa onEnter / onExit

	std::stack<GameState*> gameStack; // container de los states
	//std::vector<GameState*> m_gameStates; // (lo q usa en las diapos)

	std::list<GameState*> toBeDeleted;

public:

	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine();


	void pushState(GameState* state); // adds state without removing the previous
	void replaceState(GameState* state); // removes the previous state before adding another
	void popState(); // removes state without adding another

	void Render()const;
	void Update();

	bool Empty() const { return gameStack.empty(); }

};



#endif // !GameStateMachine_H_
