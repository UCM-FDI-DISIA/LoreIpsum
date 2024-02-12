#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include <stack>
#include <functional>

#include "GameState.h"


class GameStateMachine {

	std::stack<GameState*> gameStack;	

	std::list<GameState*> toBeDeleted;

public:

	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine();


	void pushState(GameState* state);
	void replaceState(GameState* state);
	void popState();

	void Render()const;
	void Update();

	bool Empty() const { return gameStack.empty(); }

};



#endif // !GameStateMachine_H_
