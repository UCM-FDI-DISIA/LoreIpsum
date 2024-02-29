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
#include "PaigroState.h"
#include "MovementState.h"


void GameStateMachine::init()
{

	//Estado incial
	pushState(currentState);

}

//constructor
GameStateMachine::GameStateMachine() {

	mngr_ = new ecs::Manager();

	mainMenuState = new MainMenuState();
	cityState = new CityState();
	officeState = new OfficeState();
	shopState = new ShopState();
	boardState = new BoardState();
	paigroState = new PaigroState();
	samuState = new SamuState();
	movementState = new MovementState();


	//Ponemos el estado actual
	currentState = cityState;

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

void GameStateMachine::Render() const {
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


void GameStateMachine::changeState()
{
	//Solo queremos que lo haga de ser necesario
	if (currentState != gameStack.top()) {
		replaceState(currentState);
	}
	
}

void GameStateMachine::pushState(GameState* state) {

	gameStack.push(state);		//Colocamos el nuevo GameState
	currentState->onEnter();	//Hacemos el onEnter del nuevo estado
}

void GameStateMachine::replaceState(GameState* state) {
	popState();
	pushState(state);
}

void GameStateMachine::popState() {
	gameStack.top()->onExit(); //Antes de eliminarlo hacemos el onExit del estado
	toBeDeleted.push_back(gameStack.top());
	gameStack.pop();
}