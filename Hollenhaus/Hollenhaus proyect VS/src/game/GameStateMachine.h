#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"
#include <stack>
#include <functional>
#include "../utils/Singleton.h"
#include "../utils/tweeny-3.2.0.h"

class GameState;
class Data;
class Mouse;
class Fade;

namespace ecs
{
	class Manager;
}

namespace GameStates
{
	//Enum de estados del juego
	enum game_states
	{
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
		CLUESMENU,
		MULTIPLAYER_LOBBY,
		MULTIPLAYER_PREGAME,
		MULTIPLAYER_GAME,
		MULTIPLAYER_END_GAME,
		KEYMENU
	};
}

class GameStateMachine : public Singleton<GameStateMachine>
{
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

	Mouse* mouse_;

	ecs::entity_t case_;

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
	GameState* tutorialBoardState;

	// Estados de gente
	GameState* paigroState;
	GameState* samuState;
	GameState* jimboState;
	GameState* nievesState;
	GameState* luisState;

	// Estados de menuses
	GameState* storyModeState;
	GameState* multiplayerModeState;
	GameState* optionsMainMenuState;
	GameState* cinematicIntroState;
	GameState* transitionTextMenuState;
	GameState* pauseMenuState;
	GameState* checkMazeMenuState;
	GameState* checkCluesMenuState;

	GameState* keyMenuState;
	 
	// Estados auxiliares
	GameState* movementState;

	GameState* multiplayerLobbyState;
	GameState* multiplayerPreGameState;
	GameState* multiplayerGameState;
	GameState* multiplayerEndGameState;

	/// FADE IN-OUT
	//ecs::entity_t fade;
	Fade* fade_;

	tweeny::tween<int> fadetween;
	bool toFadeIn;
	bool toFadeOut;
	int gameStateEnumValue;

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

	void setState(int state, bool fadeIn = false, bool fadeOut = false)
	{
		GameState* newState = nullptr;

		switch (state)
		{
		case GameStates::MAINMENU:
			newState = mainMenuState;
			break;
		case GameStates::CITY:
			newState = cityState;
			break;
		case GameStates::OFFICE:
			newState = officeState;
			break;
		case GameStates::SHOP:
			newState = shopState;
			break;
		case GameStates::BOARD:
			newState = boardState;
			break;
		case GameStates::PAIGRO:
			newState = paigroState;
			break;
		case GameStates::LUIS:
			newState = luisState;
			break;
		case GameStates::NIEVES:
			newState = nievesState;
			break;
		case GameStates::MATCHOVER:
			newState = matchOverState;
			break;
		case GameStates::DECKBUILDING:
			newState = deckBuildingState;
			break;
		case GameStates::MULTIPLAYER_LOBBY:
			newState = multiplayerLobbyState;
			break;
		case GameStates::MULTIPLAYER_PREGAME:
			newState = multiplayerPreGameState;
			break;
		case GameStates::MULTIPLAYER_GAME:
			newState = multiplayerGameState;
			break;
		case GameStates::MULTIPLAYER_END_GAME:
			newState = multiplayerEndGameState;
			break;
		case GameStates::TUTORIALBOARD:
			newState = tutorialBoardState;
			break;
		case GameStates::TUTORIAL:
			newState = tutorialState;
			break;
		case GameStates::STORYMODEMENU:
			newState = storyModeState;
			break;
		case GameStates::MULTIPLAYERMODEMENU:
			newState = multiplayerModeState;
			break;
		case GameStates::OPTIONSMENU:
			newState = optionsMainMenuState;
			break;
		case GameStates::TRANSITIONTEXT:
			newState = transitionTextMenuState;
			break;
		case GameStates::CINEMATICINTRO:
			newState = cinematicIntroState;
			break;
		case GameStates::PAUSEMENU:
			newState = pauseMenuState;
			break;
		case GameStates::MAZEMENU:
			newState = checkMazeMenuState;
			break;
		case GameStates::CLUESMENU:
			newState = checkCluesMenuState;
			break;
		case GameStates::KEYMENU:
			currentState = keyMenuState;
			break;
		default:
			break;
		}
		currentState = newState;
		toFadeIn = fadeIn;
		toFadeOut = fadeOut;

		gameStateEnumValue = state;

		if (toFadeIn) fadetween.forward();
		if (!toFadeIn && toFadeOut) fadetween.backward();
	}

	void initFade();

	bool Empty() const { return gameStack.empty(); }

	GameState* getCurrentState() { return currentState; }

	int getCurrentStateEnum() { return gameStateEnumValue;  }
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
