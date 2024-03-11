
#pragma once
#include "checkML.h"

class GameStateMachine;

//Probablemente haya que hacer un enum de 
class Game {
public:
	Game();
	virtual ~Game();

	void Run();
	
private:

#pragma region parametros

	Uint32 frameTime;
	Uint32 startTime;

	const Uint8 FRAME_RATE = 20;
#pragma endregion

	GameStateMachine* gameStateMachine;

	//Har�a falta un booleano de salida



	void Render() const;
	void Update();	// cleon:  "NO TENEMOS CONTROL DE TIEMPO" (== "este avi�n no tiene piloto")
	void ChangeScene();

	void HandleEvents();

};

