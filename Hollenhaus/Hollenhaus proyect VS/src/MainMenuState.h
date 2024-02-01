#ifndef MainMenuState_H_
#define MainMenuState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"
#include "Font.h"

class MainMenuState : public GameState {

	void PlayGame();

	void Exit();

public:
	
	MainMenuState(Game* game);

	void Render() const override;

};


#endif // !MainMenuState_H_
