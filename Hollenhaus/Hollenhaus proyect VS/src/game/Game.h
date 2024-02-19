
#pragma once
#include "checkML.h"

#include "MainMenuState.h"
#include "CityState.h"

#include <SDL.h>


class GameStateMachine;

//Probablemente haya que hacer un enum de 
class Game {
public:
	Game();
	virtual ~Game();

	void Run();
	
private:

#pragma region parámetros

	Uint32 frameTime;
	Uint32 startTime;

	const Uint8 FRAME_RATE = 20;
#pragma endregion

#pragma region Maquina de estados

	Game* game = this;

	GameStateMachine* gameStateMachine;

	//Enum de estados del juego
	enum game_states {
		MAINMENU = 0,
		CITY,
		OFFICE,
		SHOP,
		PLAY
	};
#pragma endregion

	//Texturas
	//TODO

	//Haría falta un booleano de salida



	void Render() const;
	void Update();

	void HandleEvents();

};

