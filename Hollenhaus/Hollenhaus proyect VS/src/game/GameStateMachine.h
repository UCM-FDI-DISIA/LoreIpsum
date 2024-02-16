#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include <stack>
#include <functional>

#include "GameState.h"

#include "../utils/Singleton.h"

namespace ecs {
	class Manager;
}

class GameStateMachine : public Singleton<GameStateMachine> {
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

public:

	inline ecs::Manager* getMngr() {
		return mngr_;
	}
	void init();
	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine();


	void pushState(GameState* state); // adds state without removing the previous
	void replaceState(GameState* state); // removes the previous state before adding another
	void popState(); // removes state without adding another

	void Render()const;
	void Update();
	void Refresh();

	bool Empty() const { return gameStack.empty(); }

};



#endif // !GameStateMachine_H_
