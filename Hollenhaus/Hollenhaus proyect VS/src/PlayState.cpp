#include "checkML.h"


#include <iostream>
#include<fstream>//para flujo de archivos entrada salida
#include<random>
#include "SDL.h"

#include "Game.h"
#include "PlayState.h"
//#include "EndState.h"


//constructor valido para partidas cargadas y mapas iniciales
PlayState::PlayState(Game* game, std::string fileName) 
	:GameState(game) {

}

//destructor
PlayState::~PlayState() {

}

void PlayState::Render()const {

	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	game->RenderClear();

	//render del background
	game->getTexture(STARS)->render();
	
	//render de los gameObjects
	GameState::Render();
}

void PlayState::Update() {

	//update de los gameObjects
	GameState::Update();
}

void PlayState::HandleEvent(const SDL_Event& ev) {

	GameState::HandleEvent(ev);

	if (ev.type == SDL_KEYDOWN &&
		ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

		//cambiar al estado de pausa
	}
}
