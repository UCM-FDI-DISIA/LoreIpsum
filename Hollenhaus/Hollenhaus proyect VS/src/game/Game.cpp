
#include <../pchs/pch.h>

#include "Game.h"
#include "checkML.h"


#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

#include "GameStateMachine.h"

Game::Game()
{
	SDLUtils::init("Hollenhaus", 800, 600,
		"resources/config/resources.json", "resources/config/cards.json", "resources/config/dialoguesV1.json",
		"resources/config/npcs.json", "resources/config/keytexts.json");

	GameStateMachine::instance()->init();
	gameStateMachine = GameStateMachine::instance();
	
	auto& sdl = *SDLUtils::instance();
	sdl.presentRenderer();

#ifdef _DEBUG
	std::cout << "Mapping fullscreen toggle to F11 key" << std::endl;
	ih().insertFunction(ih().KEY_F11_DOWN, [] { sdlutils().toggleFullScreen(); });
#endif
}

Game::~Game()
{
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
	while (!ih().closeWindowEvent() && !gameStateMachine->Empty())
	{
		//actualizar el start time
		startTime = SDL_GetTicks();

		//ejecutar el bucle principal
		HandleEvents();
		Render();
		Update();
		ChangeScene();

		//calcular el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//prueba para ver cuanto tardan los frames
		//std::cout << frameTime << std::endl;

		//si queda tiempo de frame, suspender el programa el tiempo que queda
		if (frameTime < FRAME_RATE)
		{
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}

	while(!gameStateMachine->Empty()) {
		gameStateMachine->popState();
	}

}


void Game::Render() const
{
	sdlutils().clearRenderer();
	gameStateMachine->Render();
	sdlutils().presentRenderer();
}

void Game::Update()
{
	gameStateMachine->Update();
}

void Game::ChangeScene()
{
	gameStateMachine->changeState();
}

void Game::HandleEvents()
{
	ih().refresh();	
}
