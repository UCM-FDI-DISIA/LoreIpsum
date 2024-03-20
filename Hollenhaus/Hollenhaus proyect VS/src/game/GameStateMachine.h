#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"
#include <stack>
#include <functional>
#include "../utils/Singleton.h"


class GameState;
class Data;
class Mouse;

namespace ecs
{
	class Manager;
}

namespace GameStates
{
	//Enum de estados del juego
	enum game_states {
		MAINMENU = 0,
		CITY,
		OFFICE,
		SHOP,
		BOARD,
		PAIGRO,
		SAMU,
		NIEVES,
		MATCHOVER
	};
}
	

class GameStateMachine : public Singleton<GameStateMachine>
{
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

	Mouse* mouse_;

	//Creaci�n de los distintos estados del juego
	GameState* currentState;
	GameState* mainMenuState;
	GameState* cityState;
	GameState* officeState;
	GameState* shopState;
	GameState* boardState;
	GameState* paigroState;
	GameState* samuState;
	GameState* jimboState;
	GameState* nievesState;
	GameState* movementState;
	GameState* matchOverState;

public:
	ecs::Manager* getMngr()
	{
		return mngr_;
	}

	void init();
	//constructor
	GameStateMachine();

	//destructor
	~GameStateMachine() override;

	void changeState();
	void pushState(GameState* state); // adds state without removing the previous
	void replaceState(GameState* state); // removes the previous state before adding another
	void popState(); // removes state without adding another

	void Render() const;
	void Update();
	void Refresh();

	inline void setState(int state) {

		switch (state)
		{
		case GameStates::MAINMENU:
			currentState = mainMenuState;
			break;
		case GameStates::CITY:
			currentState = cityState;
			break;
		case GameStates::OFFICE:
			currentState = officeState;
			break;
		case GameStates::SHOP:
			currentState = shopState;
			break;
		case GameStates::BOARD:
			currentState = boardState;
			break;
		case GameStates::PAIGRO:
			currentState = paigroState;
			break;
		case GameStates::SAMU:
			currentState = samuState;
			break;
		case GameStates::NIEVES:
			currentState = nievesState;
			break;
		case GameStates::MATCHOVER:
			currentState = matchOverState;
			break;
		default:
			break;
		}
	};
	bool Empty() const { return gameStack.empty(); }

	GameState* getCurrentState() { return currentState; }
};

// --------
// forma de usar el singleton Manager
// GameStateMachine::instance()->getMngr()->method() / EN VEZ DE ESTO
// mngr().method() / ESCRIBIR ESTO
inline ecs::Manager& mngr()
{
	return *GameStateMachine::instance()->getMngr();
}
#endif // !GameStateMachine_H_
