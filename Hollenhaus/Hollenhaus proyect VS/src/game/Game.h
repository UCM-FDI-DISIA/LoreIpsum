
#pragma once
#include "checkML.h"


#include "GameStateMachine.h"

class Game {
public:
	Game();
	virtual ~Game();

	void Run();
	
private:

	GameStateMachine* gameStateMachine;

	Uint32 frameTime;
	Uint32 startTime;

	const Uint8 FRAME_RATE = 20;

	void Render() const;
	void Update();

	void HandleEvents();

};

