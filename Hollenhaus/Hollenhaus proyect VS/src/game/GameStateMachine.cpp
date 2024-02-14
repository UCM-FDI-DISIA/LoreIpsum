#include "checkML.h"

#include <iostream>
#include <SDL.h>


#include "GameStateMachine.h"
#include "MainMenuState.h"

//constructor
GameStateMachine::GameStateMachine()  {

	//inicializamos la pila con el estado del menu inicial
	pushState(new MainMenuState());
}

//destructor
GameStateMachine::~GameStateMachine() {

	//destruye uno a uno todos los estados apilados que queden
	while (!gameStack.empty()) {
		delete gameStack.top();
		gameStack.pop();
	}

}


void GameStateMachine::Render() const{
	if (Empty()) return;
	gameStack.top()->render();
}

void GameStateMachine::Update() {
	if (Empty()) return;
	gameStack.top()->update();
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