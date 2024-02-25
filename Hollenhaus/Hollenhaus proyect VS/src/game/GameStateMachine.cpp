#include "checkML.h"

#include <iostream>
#include <SDL.h>


#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "CityState.h"
#include "OfficeState.h"
#include "ShopState.h"
#include "BoardState.h"
#include "SamuState.h"
#include "JimboState.h"
#include "Manager.h"


void GameStateMachine::init()
{
	mngr_ = new ecs::Manager();

	mainMenuState = new MainMenuState();
	cityState = new CityState();
	officeState = new OfficeState();
	shopState = new ShopState();
	boardState = new BoardState();

	//Ponemos el estado actual
	currentState = mainMenuState;

	//Estado incial
	pushState(currentState);


	pushState(new SamuState());
}

//constructor
GameStateMachine::GameStateMachine()  {

	//init();
	//inicializamos la pila con el estado del menu inicial

}

//destructor
GameStateMachine::~GameStateMachine() {

	//destruye uno a uno todos los estados apilados que queden
	while (!gameStack.empty()) {
		delete gameStack.top();
		gameStack.pop();
	}

	delete mngr_;
}


void GameStateMachine::Render() const{
	if (Empty()) return;
	gameStack.top()->render();
}

void GameStateMachine::Update() {
	if (Empty()) return;
	gameStack.top()->update();

	//para el manager
	Refresh();
}

void GameStateMachine::Refresh()
{
	gameStack.top()->refresh();
}

void GameStateMachine::setState(int state)
{
	GameState* newState;

	switch (state)
	{
	case MAINMENU:
		newState = mainMenuState;
		break;
	case CITY:
		newState = cityState;
		break;
	case OFFICE:
		newState = officeState;
		break;
	case SHOP:
		newState = shopState;
		break;
	case BOARD:
		newState = boardState;
		break;
	default:
		break;
	}

	//Hacemos el exit del estado actual
	
}

void GameStateMachine::pushState(GameState* state) {
	gameStack.push(state);
}

void GameStateMachine::replaceState(GameState* state) {
	popState();
	pushState(state);
}

void GameStateMachine::popState() {
	toBeDeleted.push_back(gameStack.top());
	gameStack.pop();
}