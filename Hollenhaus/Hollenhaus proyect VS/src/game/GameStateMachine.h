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
		TUTORIALBOARD,
		TUTORIAL,
		STORYMODEMENU,
		MULTIPLAYERMODEMENU,
		OPTIONSMENU,
		TRANSITIONTEXT,
		CINEMATICINTRO,
		PAUSEMENU,
		MAZEMENU,
		CLUESMENU
	};
}

class GameStateMachine : public Singleton<GameStateMachine>
{
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

	Mouse* mouse_;

	//Creacion de los distintos estados del juego
	// 
	// Current
	GameState* currentState;

	// Estados de juego
	GameState* mainMenuState;
	GameState* cityState;
	GameState* officeState;
	GameState* shopState;
	GameState* matchOverState;
	GameState* boardState;
	GameState* deckBuildingState;
	GameState* tutorialState;

	// Estados de gente
	GameState* paigroState;
	GameState* samuState;
	GameState* jimboState;
	GameState* nievesState;
	GameState* luisState;
	GameState* deckBuildingState;
	GameState* tutorialBoardState;

	// Estados de menuses
	GameState* storyModeState;
	GameState* multiplayerModeState;
	GameState* optionsMainMenuState;
	GameState* cinematicIntroState;
	GameState* transitionTextMenuState;
	GameState* pauseMenuState;
	GameState* checkMazeMenuState;
	GameState* checkCluesMenuState;
	 
	// Estados auxiliares
	GameState* movementState;

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
		case GameStates::TUTORIALBOARD:
			currentState = tutorialBoardState;
			break;
		case GameStates::TUTORIAL:
			currentState = tutorialState;
			break; 
		case GameStates::STORYMODEMENU:
				currentState = storyModeState;
			break; 
		case GameStates::MULTIPLAYERMODEMENU:
			currentState = multiplayerModeState;
			break;
		case GameStates::OPTIONSMENU:
			currentState = optionsMainMenuState;
			break; 
		case GameStates::TRANSITIONTEXT:
			currentState = transitionTextMenuState;
			break; 
		case GameStates::CINEMATICINTRO:
			currentState = cinematicIntroState;
			break; 
		case GameStates::PAUSEMENU:
			currentState = pauseMenuState;
			break; 
		case GameStates::MAZEMENU:
			currentState = checkMazeMenuState;
			break; 
		case GameStates::CLUESMENU:
			currentState = checkCluesMenuState;
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
