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
		MAINMENU,
		CITY,
		OFFICE,
		SHOP,
		BOARD,
		PAIGRO,
		LUIS,
		NIEVES,
		MATCHOVER,
		DECKBUILDING,
		MULTIPLAYER_LOBBY,
		MULTIPLAYER_PREGAME,
		MULTIPLAYER_GAME,
		MULTIPLAYER_END_GAME
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
	GameState* luisState;
	GameState* deckBuildingState;

	GameState* multiplayerLobby;
	GameState* multiplayerPreGame;
	GameState* multiplayerGame;
	GameState* multiplayerEndGame;

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
		case GameStates::LUIS:
			currentState = luisState;
			break;
		case GameStates::NIEVES:
			currentState = nievesState;
			break;
		case GameStates::MATCHOVER:
			currentState = matchOverState;
			break;
		case GameStates::DECKBUILDING:
			currentState = deckBuildingState;
			break;
		case GameStates::MULTIPLAYER_LOBBY:
			currentState = multiplayerLobby;
			break;
		case GameStates::MULTIPLAYER_PREGAME:
			currentState = multiplayerPreGame;
			break;
		case GameStates::MULTIPLAYER_GAME:
			currentState = multiplayerGame;
			break;
		case GameStates::MULTIPLAYER_END_GAME:
			currentState = multiplayerEndGame;
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
