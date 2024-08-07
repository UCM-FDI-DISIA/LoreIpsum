#include <../pchs/pch.h>

#include <iostream>
#include <SDL.h>
#include "GameStateMachine.h"

#include "gamestates/MainMenuState.h"
#include "gamestates/CityState.h"
#include "gamestates/OfficeState.h"
#include "gamestates/ShopState.h"
#include "gamestates/MatchOverState.h"
#include "gamestates/DeckBuildingState.h"
#include "gamestates/tutorialState.h"
#include "gamestates/cinematicIntroState.h"
#include "gamestates/FirstState.h"
#include "gamestates/cinematicOutroState.h"
#include "gamestates/CasinoState.h"
#include "gamestates/Solitaire.h"
#include "gamestates/SolitaireQuestion.h"

#include "gamestates/SamuState.h"
#include "gamestates/JimboState.h"
#include "gamestates/AndresState.h"
#include "gamestates/LuisState.h"
#include "gamestates/PaigroState.h"
#include "gamestates/NievesState.h"
#include "gamestates/MatchOverState.h"
#include "gamestates/DeckBuildingState.h"

#include "gamestates/MultiplayerLobbyState.h"
#include "gamestates/MultiplayerPreGameState.h"
#include "gamestates/MultiplayerGameState.h"
#include "gamestates/MultiplayerEndGameState.h"
#include "gamestates/TutorialBoardState.h"

#include "gamestates/checkCluesMenuState.h"
#include "gamestates/checkMazeMenuState.h"
#include "gamestates/multiplayerModeState.h"
#include "gamestates/optionsMainMenuState.h"
#include "gamestates/pauseMenuState.h"
#include "gamestates/storyModeState.h"
#include "gamestates/transitionTextMenuState.h"

#include "components/managers/Manager.h"
#include "Mouse.h"
#include "gamestates/GameState.h"
#include "Data.h"
#include "Fade.h"
#include "CaseManager.h"
#include "gamestates/EndGameState.h"
#include "gamestates/FirstState.h"
#include "gamestates/LogoState.h"

constexpr Uint8 FADE_SPEED = 30;

void GameStateMachine::init()
{
	currentState->loadDataIfExists();
	//Estado incial
	pushState(currentState);

	initFade();
}

//constructor
GameStateMachine::GameStateMachine()
{
	mngr_ = new ecs::Manager();
	mouse_ = new Mouse("mouse", 2);
	fade_ = new Fade(0);

	case_ = new CaseManager();

	// Creacion de los estados
	// Estados del juego
	cityState = new CityState();
	officeState = new OfficeState();
	shopState = new ShopState();
	deckBuildingState = new DeckBuildingState();
	tutorialState = new TutorialState();
	endGameState = new EndGameState();

	// Estados de menuses
	firstState = new FirstState();
	logoSate = new LogoState();
	mainMenuState = new MainMenuState();
	storyModeState = new StoryModeState();
	multiplayerModeState = new MultiplayerModeState();
	optionsMainMenuState = new OptionsMainMenuState();
	transitionTextMenuState = new TransitionTextMenuState();
	cinematicIntroState = new CinematicIntroState();
	cinematicOutroState = new CinematicOutroState();
	pauseMenuState = new PauseMenuState();
	checkMazeMenuState = new CheckMazeMenuState();
	checkCluesMenuState = new CheckCluesMenuState();
	matchOverState = new MatchOverState();

	// Estados de gente
	samuState = new SamuState();
	jimboState = new JimboState();
	nievesState = new NievesState();
	luisState = new LuisState();
	tutorialBoardState = new TutorialBoardState();
	tutorialDeckbuildingState = new DeckBuildingState(true);
	tutorialShopState = new ShopState(true);
	tutorialCityState = new CityState(true);
	tutorialOfficeState = new OfficeState(true);


	multiplayerLobbyState = new MultiplayerLobbyState();
	multiplayerPreGameState = new MultiplayerPreGameState();
	multiplayerGameState = new MultiplayerGameState();
	multiplayerEndGameState = new MultiplayerEndGameState();

	//extra
	casinoState = new CasinoState();
	solitaireState = new Solitaire();
	solitaireQuestionState = new SolitaireQuestion();

	// Ponemos el estado actual
	//currentState = new MainMenuState();
	// tutorialDeckbuildingState

	currentState = casinoState;

	// settea la data en el current state para acceder a ella desde cualquier estado
	currentState->setData(new Data());
}

// destructor
GameStateMachine::~GameStateMachine()
{
	delete mouse_;
	delete fade_;
	delete case_;

	delete cityState;
	delete officeState;
	delete shopState;
	delete deckBuildingState;
	delete tutorialState;
	delete endGameState;
	delete tutorialBoardState;
	delete tutorialCityState;
	delete tutorialDeckbuildingState;
	delete tutorialOfficeState;
	delete tutorialShopState;

	delete logoSate;
	delete mainMenuState;
	delete storyModeState;
	delete multiplayerModeState;
	delete optionsMainMenuState;
	delete transitionTextMenuState;
	delete cinematicIntroState;
	delete cinematicOutroState;
	delete pauseMenuState;
	delete checkMazeMenuState;
	delete checkCluesMenuState;
	delete matchOverState;

	delete samuState;
	delete jimboState;
	delete nievesState;
	delete luisState;

	delete multiplayerLobbyState;
	delete multiplayerPreGameState;
	delete multiplayerGameState;
	delete multiplayerEndGameState;
	delete casinoState;
	delete solitaireState;
	delete solitaireQuestionState;
	delete currentState->getData();
	currentState->setData(nullptr);

	delete mngr_;

	mainMenuState = nullptr;
	cityState = nullptr;
	officeState = nullptr;
	shopState = nullptr;
	//boardState = nullptr;
	samuState = nullptr;
	jimboState = nullptr;
	nievesState = nullptr;
	matchOverState = nullptr;
	luisState = nullptr;
	deckBuildingState = nullptr;
	tutorialBoardState = nullptr;
	tutorialCityState = nullptr;
	tutorialDeckbuildingState = nullptr;
	tutorialOfficeState = nullptr;
	tutorialShopState = nullptr;

}

void GameStateMachine::Render() const
{
	if (Empty()) return;
	gameStack.top()->render();
	fade_->render();
	mouse_->render();
}

void GameStateMachine::Update()
{
	if (Empty()) return;

	/// FADE OUTOF BLACK
	if (toFadeOut && !toFadeIn) // no fade in porque ha de ocurrir en los updates despues del fadeout
	{
		if (fadetween.progress() <= 0.0)
		{
			fadetween.forward();
			toFadeOut = false;
			return;
		}
		fadetween.step(1);
		fade_->setOpacity(fadetween.peek());
	}

	gameStack.top()->update();
	mouse_->update();
	case_->update();
	//para el manager
	Refresh();
}

void GameStateMachine::Refresh()
{
	gameStack.top()->refresh();
}

void GameStateMachine::initFade()
{
	/// FADE TWEEN
	fadetween =
		tweeny::from(0)
		.to(255)
		.during(FADE_SPEED)
		.via(tweeny::easing::linear);

	if (toFadeIn) fadetween.forward();
	if (!toFadeIn && toFadeOut) fadetween.backward();
}

void GameStateMachine::setTUTORIAL_DECKBUILDING_COMPLETE(bool a)
{
	dbt_c = a;

	// GUARDA EN EL SAVE
	currentState->setTUTORIAL_DECKBUILDING_COMPLETE(a);
	currentState->saveData();
}

void GameStateMachine::setTUTORIAL_CITY_COMPLETE(bool a)
{
	ct_c = a;

	// GUARDA EN EL SAVE
	currentState->setTUTORIAL_CITY_COMPLETE(a);
	currentState->saveData();
}

void GameStateMachine::setTUTORIAL_BOARD_COMPLETE(bool a)
{
	bt_c = a;

	// GUARDA EN EL SAVE
	currentState->setTUTORIAL_BOARD_COMPLETE(a);
	currentState->saveData();
}

void GameStateMachine::setTUTORIAL_SHOP_COMPLETE(bool a)
{
	st_c = a;

	// GUARDA EN EL SAVE
	currentState->setTUTORIAL_SHOP_COMPLETE(a);
	currentState->saveData();
}


void GameStateMachine::changeState()
{
	//Solo queremos que lo haga de ser necesario
	if (currentState != gameStack.top())
	{
		/// FADE INTO BLACK
		if (toFadeIn)
		{
			// si ha de hacer fade
			if (fadetween.progress() >= 1.0)
			{
				// si ya ha acabado el fade
				fadetween.backward(); // cambia el sentido para hacer fadein
				toFadeIn = false;
				replaceState(currentState);
				return;
			}
			fadetween.step(1); // avanza
			fade_->setOpacity(fadetween.peek());
		} // si no, cambio automatico
		else
			replaceState(currentState);
	}
}

void GameStateMachine::pushState(GameState* state)
{
	gameStack.push(state); //Colocamos el nuevo GameState
	currentState->onEnter(); //Hacemos el onEnter del nuevo estado

	/// GUARRADA MAXIMA PARA EL MOUSE: al cambiar de estados se borran los callbacks del ih()
	///	y estropea el comportamiento del cursor, hay que mirar como evitar eso 
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { mouse_->changeFrame(1); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { mouse_->changeFrame(0); });
}

void GameStateMachine::replaceState(GameState* state)
{
	popState();
	pushState(state);
}

void GameStateMachine::popState()
{
	gameStack.top()->onExit(); //Antes de eliminarlo hacemos el onExit del estado
	toBeDeleted.push_back(gameStack.top());
	gameStack.pop();

	ih().clearFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { mouse_->changeFrame(1); });
	ih().clearFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { mouse_->changeFrame(0); });
}
