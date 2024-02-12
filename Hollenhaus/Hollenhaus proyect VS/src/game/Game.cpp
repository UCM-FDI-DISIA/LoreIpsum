#include "checkML.h"
#include "Game.h"
#include "../sdlutils/SDLUtils.h"


Game::Game()
{
	SDLUtils::init("Hollenhaus", 800, 600, "./resources/config/resources.json");

	gameStateMachine = new GameStateMachine();
}

Game::~Game()
{
	delete gameStateMachine;
}

void Game::Run()
{
	/*
	version control total pero consume mas recursos

	while (!exit) {
		HandleEvents();
		//actualizar el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//si va a pasar un frame
		if (frameTime >= FRAME_RATE) {
			Update();
			//actualizar el startTime para tiempo de frames
			startTime = SDL_GetTicks();
		}
		Render();
	}
	*/

	//version suspendiendo el programa,consume menos recursos	
	while (!InputHandler::instance()->closeWindowEvent() && !gameStateMachine->Empty()) {
		//actualizar el start time
		startTime = SDL_GetTicks();

		//ejecutar el bucle principal
		HandleEvents();
		Update();
		Render();

		//calcular el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//prueba para ver cuanto tardan los frames
		//std::cout << frameTime << std::endl;

		//si queda tiempo de frame, suspender el programa el tiempo que queda
		if (frameTime < FRAME_RATE) {

			SDL_Delay(FRAME_RATE - frameTime);
		}
	}

}

void Game::Render() const
{
	gameStateMachine->Render();
}

void Game::Update()
{
	gameStateMachine->Update();
}

void Game::HandleEvents()
{
	InputHandler::instance()->refresh();	
}
