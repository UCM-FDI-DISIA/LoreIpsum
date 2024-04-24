#include <../pchs/pch.h>


#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		auto game = new Game();

		game->Run();

		delete game;
	}
	catch (exception e)
	{
		SDL_ShowSimpleMessageBox(0, "Error tu vieja", e.what(), nullptr);
	}

	return 0;
}
