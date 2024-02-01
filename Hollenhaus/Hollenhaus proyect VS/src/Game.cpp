#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <vector>

#include "Game.h"


//constructor 
Game::Game(){

	InitializeSDL();

	TTF_Init();

	font = new Font("resources/fonts/PressStart2P-Regular.ttf",25);
	
	//LoadTextures();


	gameStateMachine = new GameStateMachine(this);


}

//destructor
Game::~Game() {


	delete gameStateMachine;

	//delete de las texturas(dentro se hace el SDL_DestroyTexture)
	/*
	for (int i = 0; i < NUM_TEXTURAS; i++) {
		delete arrayTexturas[i];
	}

	*/
	delete font;

	
	TTF_Quit();

	//destructores(renderer window, y sdl quit)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Render() const{
	gameStateMachine->Render();

	//renderizar todo la cola
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	gameStateMachine->Update();
}

void Game::HandleEvents() {

	SDL_Event evento;

	//carga los eventos 
	while (SDL_PollEvent(&evento) && !exit) {
		//trata los eventos en funcion de su tipo()
		if (evento.type == SDL_QUIT) {
			exit = true;
		}
		else {
			gameStateMachine->HandleEvents(evento);		
		}
	}
}

void Game::Run() {
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
	while (!exit && !gameStateMachine->Empty()) {
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


void Game::InitializeSDL() {
	//inicializar sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//crear la ventana
	window = SDL_CreateWindow("Practica 1 TPV", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	//crear el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//si ha fallado la carga salir, sino codigo del programa
	if (window == nullptr || renderer == nullptr)
		throw SDLError();
}

//cambiar logica de texturas por clase label...
void Game::LoadTextures() {

	//creacion del vector de las texturas
	std::vector<TextureInfo> textInfo;


	textInfo.push_back(TextureInfo("aliens.png", 3, 2));
	textInfo.push_back(TextureInfo("bunker.png", 1, 4));
	textInfo.push_back(TextureInfo("spaceship.png", 1, 1));
	textInfo.push_back(TextureInfo("stars.png", 1, 1));
	textInfo.push_back(TextureInfo("ufo.png", 1, 2));

	textInfo.push_back(TextureInfo("fondos/mainMenu.png", 1, 1));
	textInfo.push_back(TextureInfo("objetos/shield_reward.png", 1, 1));
	textInfo.push_back(TextureInfo("objetos/shield.png", 1, 1));
	textInfo.push_back(TextureInfo("objetos/bomb.png", 1, 1));


	//crear las texturas de la ttf
	arrayTexturas[SCORE] = font->generateTexture(renderer, "SCORE:", SDL_Color{ 255,255,255,255 });
	arrayTexturas[NUEVA_PARTIDA] = font->generateTexture(renderer, "NUEVA PARTIDA", SDL_Color{ 255,255,255,255 });
	arrayTexturas[CARGAR_PARTIDA] = font->generateTexture(renderer, "CARGAR PARTIDA", SDL_Color{ 255,255,255,255 });
	arrayTexturas[SALIR] = font->generateTexture(renderer, "SALIR", SDL_Color{ 255,255,255,255 });
	arrayTexturas[GUARDAR_PARTIDA] = font->generateTexture(renderer, "GUARDAR PARTIDA", SDL_Color{ 255,255,255,255 });
	arrayTexturas[CONTINUAR] = font->generateTexture(renderer, "CONTINUAR", SDL_Color{ 255,255,255,255 });
	arrayTexturas[VOLVER_AL_MENU] = font->generateTexture(renderer, "VOLVER AL MENU", SDL_Color{ 255,255,255,255 });
	arrayTexturas[GAMEOVER] = font->generateTexture(renderer, "GAMEOVER", SDL_Color{ 255,255,255,255 });
	arrayTexturas[HAS_GANADO] = font->generateTexture(renderer, "HAS GANADO", SDL_Color{ 255,255,255,255 });
	arrayTexturas[CODIGO] = font->generateTexture(renderer, "CODIGO:", SDL_Color{ 255,255,255,255 });


	//crear el resto de texturas
	for (int i = 0; i < SCORE; i++) {
		arrayTexturas[i] = new Texture(renderer, (TEXTURE_ROOT + textInfo[i].fileName).c_str(),
			textInfo[i].horizontalFrames, textInfo[i].verticalFrames);
	}

}