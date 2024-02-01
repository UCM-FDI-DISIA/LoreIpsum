#include "checkML.h"

#include <iostream>
#include <SDL.h>


#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"

//constructor
GameStateMachine::GameStateMachine(Game* game) : game(game) {

	//inicializamos la pila con el estado del menu inicial
	gameStack.push(new MainMenuState(game));
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

void GameStateMachine::HandleEvents(const SDL_Event& ev) {
	if (Empty()) return;
	gameStack.top()->HandleEvent(ev);

	while (!toBeDeleted.empty()) {
		delete toBeDeleted.front();
		toBeDeleted.pop_front();
	}
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