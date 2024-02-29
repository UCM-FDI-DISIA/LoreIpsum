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

public:

	inline ecs::Manager* getMngr() {
		return mngr_;
	}
	void init();
	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine();

	void changeState();
	void pushState(GameState* state); // adds state without removing the previous
	void replaceState(GameState* state); // removes the previous state before adding another
	void popState(); // removes state without adding another

	void Render()const;
	void Update();
	void Refresh();

	inline void setState(int state) {

		switch (state)
		{
		case MAINMENU:
			currentState = mainMenuState;
			break;
		case CITY:
			currentState = cityState;
			break;
		case OFFICE:
			currentState = officeState;
			break;
		case SHOP:
			currentState = shopState;
			break;
		case BOARD:
			currentState = boardState;
			break;
		case PAIGRO:
			currentState = paigroState;
			break;
		case SAMU:
			currentState = samuState;
			break;
		default:
			break;
		}

		
	};
	bool Empty() const { return gameStack.empty(); }

private:
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

	//Enum de estados del juego
	enum game_states {
		MAINMENU = 0,
		CITY,
		OFFICE,
		SHOP,
		BOARD,
		PAIGRO,
		SAMU
	};

	//Creaci�n de los distintos estados del juego
	GameState *currentState;
	GameState *mainMenuState;
	GameState *cityState;
	GameState *officeState;
	GameState *shopState;
	GameState *boardState;
	GameState *paigroState;
	GameState *samuState;
	GameState* movementState;

};


// --------
// forma de usar el singleton Manager
// GameStateMachine::instance()->getMngr()->method() / EN VEZ DE ESTO
// mngr().method() / ESCRIBIR ESTO
inline ecs::Manager& mngr() {
	return *GameStateMachine::instance()->getMngr();
}
#endif // !GameStateMachine_H_
