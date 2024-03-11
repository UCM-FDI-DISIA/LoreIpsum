#include "pch.h"
#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "CityState.h"
#include "OfficeState.h"
#include "ShopState.h"
#include "SamuState.h"
#include "JimboState.h"
#include "AndresState.h"
#include "LuisState.h"
#include "Manager.h"
#include "PaigroState.h"
#include "NievesState.h"
#include "Mouse.h"
#include "GameState.h"
#include "MatchOverState.h"


void GameStateMachine::init()
{

	//Estado incial
	pushState(currentState);

}

//constructor
GameStateMachine::GameStateMachine() {

	mngr_ = new ecs::Manager();
	mouse_ = new Mouse("mouse", 2);

	//Creación de los estados
	mainMenuState = new MainMenuState();
	cityState = new CityState();
	officeState = new OfficeState();
	shopState = new ShopState();
	samuState = new SamuState();
	nievesState = new NievesState();
	matchOverState = new MatchOverState();

	// Ponemos el estado actual
	currentState = mainMenuState;

	// crea la data en el current state
	currentState->setData(new Data());
}

// destructor
GameStateMachine::~GameStateMachine() {

	//destruye uno a uno todos los estados apilados que queden
	while (!gameStack.empty()) {
		delete gameStack.top();
		gameStack.pop();
	}
	delete mouse_;
	delete mngr_;
}

void GameStateMachine::Render() const {
	if (Empty()) return;
	gameStack.top()->render();
	mouse_->render();
}

void GameStateMachine::Update() {
	if (Empty()) return;

	gameStack.top()->update();
	mouse_->update();
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
		/// GUARRADA MAXIMA PARA EL MOUSE: al cambiar de estados se borran los callbacks del ih()
		///	y estropea el comportamiento del cursor, hay que mirar como evitar eso 
		ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { mouse_->changeFrame(1); });
		ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] {  mouse_->changeFrame(0); });
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