
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

	GameStateMachine* gameStateMachine;

	//Haría falta un booleano de salida



	void Render() const;
	void Update();
	void ChangeScene();

	void HandleEvents();

};

