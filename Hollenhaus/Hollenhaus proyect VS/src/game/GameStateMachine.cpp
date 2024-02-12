#include "checkML.h"

#include <iostream>
#include <SDL.h>


#include "GameStateMachine.h"

//constructor
GameStateMachine::GameStateMachine()  {

	//inicializamos la pila con el estado del menu inicial
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
	gameStack.top()->Render();
}

void GameStateMachine::Update() {
	if (Empty()) return;
	gameStack.top()->Update();
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