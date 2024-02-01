#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Game.h"

void GameState::Render() const {
	for (GameObject& ob : gameObjects) ob.Render();
}

void GameState::Update() {
	for (GameObject& ob : gameObjects) ob.Update();
}

void GameState::HandleEvent(const SDL_Event& ev){
	for (EventHandler*& ob : handleEventsObjects) ob->handleEvent(ev);
}


void GameState::addEventListener(EventHandler* handler) {
	handleEventsObjects.push_back(handler);
}

void GameState::addObject(GameObject* gameObject) {
	gameObjects.push_back(gameObject);
}

SDL_Renderer* GameState::getRenderer() { return game->getRenderer(); }