#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	try {
		Game* game = new Game();

		game->Run();

		delete game;
	}
	catch (InvadersError error) {
		SDL_ShowSimpleMessageBox(0, "Untitled", error.what(), nullptr);
	}

	return 0;
}
