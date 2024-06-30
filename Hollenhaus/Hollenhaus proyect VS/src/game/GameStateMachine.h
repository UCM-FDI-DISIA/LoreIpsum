#ifndef GameStateMachine_H_
#define GameStateMachine_H_

//Checkml
#include <game/checkML.h>

#include <stack>
#include <functional>
#include "../utils/Singleton.h"
#include "../utils/tweeny-3.2.0.h"
#include "gamestates/GameState.h"

class GameState;
class Data;
class Mouse;
class Fade;
class CaseManager;

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
		CINEMATICOUTRO,
		PAUSEMENU,
		MAZEMENU,
		CLUESMENU,
		MULTIPLAYER_LOBBY,
		MULTIPLAYER_PREGAME,
		MULTIPLAYER_GAME,
		MULTIPLAYER_END_GAME,
		ENDGAME,
		TUTORIAL_DECKBUILDING,
		TUTORIAL_SHOP,
		TUTORIAL_CITY,
		TUTORIAL_OFFICE,
		LOGOSTATE,
		FIRST,
		CASINO,
		SOLITAIRE,
		SOLITAIREQUESTION
	};
}

class GameStateMachine : public Singleton<GameStateMachine>
{
	std::stack<GameState*> gameStack; // container de los states

	std::list<GameState*> toBeDeleted;

	friend Singleton<GameStateMachine>;

	ecs::Manager* mngr_;

	Mouse* mouse_;

	CaseManager* case_;

	//Creacion de los distintos estados del juego
	// 
	// Current
	GameState* currentState;

	// Estados de juego
	GameState* firstState;
	GameState* logoSate;
	GameState* mainMenuState;
	GameState* cityState;
	GameState* officeState;
	GameState* shopState;
	GameState* matchOverState;
	GameState* boardState;
	GameState* deckBuildingState;
	GameState* tutorialState;
	GameState* tutorialBoardState;
	GameState* endGameState;
	GameState* tutorialDeckbuildingState;
	GameState* tutorialShopState;
	GameState* tutorialOfficeState;
	GameState* tutorialCityState;


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
	GameState* cinematicOutroState;
	GameState* transitionTextMenuState;
	GameState* pauseMenuState;
	GameState* checkMazeMenuState;
	GameState* checkCluesMenuState;

	// Estados auxiliares
	GameState* movementState;

	GameState* multiplayerLobbyState;
	GameState* multiplayerPreGameState;
	GameState* multiplayerGameState;
	GameState* multiplayerEndGameState;
	GameState* casinoState;
	GameState* solitaireState;
	GameState* solitaireQuestionState;

	/// FADE IN-OUT
	//ecs::entity_t fade;
	Fade* fade_;

	tweeny::tween<int> fadetween;
	bool toFadeIn;
	bool toFadeOut;
	int gameStateEnumValue;

	bool dbt_c = false;
	bool ct_c = false;
	bool bt_c = false;
	bool st_c = false;

public:
	ecs::Manager* getMngr()
	{
		return mngr_;
	}

	CaseManager* caseMngr()
	{
		return case_;
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

	void setState(int state, bool fadeIn = true, bool fadeOut = true)
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
		case GameStates::CINEMATICOUTRO:
			newState = cinematicOutroState;
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
		case GameStates::ENDGAME:
			newState = endGameState;
			break;
		case GameStates::TUTORIAL_DECKBUILDING:
			newState = tutorialDeckbuildingState;
			break;
		case GameStates::TUTORIAL_SHOP:
			newState = tutorialShopState;
			break;
		case GameStates::TUTORIAL_CITY:
			newState = tutorialCityState;
			break;
		case GameStates::TUTORIAL_OFFICE:
			newState = tutorialOfficeState;
			break;
		case GameStates::LOGOSTATE:
			newState = logoSate;
			break;
		case GameStates::FIRST:
			newState = firstState;
			break;
		case GameStates::CASINO:
			newState = casinoState;
			break;
		case GameStates::SOLITAIRE:
			newState = solitaireState;
			break;
		case GameStates::SOLITAIREQUESTION:
			newState = solitaireQuestionState;
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

	int getCurrentStateEnum() { return gameStateEnumValue; }


	// TUTORIAL
	bool TUTORIAL_DECKBUILDING_COMPLETE() { return dbt_c; }
	void setTUTORIAL_DECKBUILDING_COMPLETE(bool a);
	bool TUTORIAL_CITY_COMPLETE() { return ct_c; }
	void setTUTORIAL_CITY_COMPLETE(bool a);
	bool TUTORIAL_BOARD_COMPLETE() { return bt_c; }
	void setTUTORIAL_BOARD_COMPLETE(bool a);
	bool TUTORIAL_SHOP_COMPLETE() { return st_c; }
	void setTUTORIAL_SHOP_COMPLETE(bool a);
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
