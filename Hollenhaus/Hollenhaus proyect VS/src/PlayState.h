#ifndef PlayState_H_
#define PlayState_H_

#include "checkML.h"


#include <iostream>
#include <vector>
#include <random>
#include <string> //para usar to string
#include <filesystem>

#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"




#include "InvadersError.h"


#include "GameState.h"
#include "Game.h"
	
using uint = unsigned int;


//enumerado tipos de objetos
enum ObjectTypes{CANNON,ALIEN,SHOOTER_ALIEN,MOTHERSHIP,BUNKER_TYPE,UFO_TYPE,LASER};

//ruta del mapa
const std::string MAP_PATH = "mapas/original.txt";

//puntuaciones de los aliens y del  ufo

const int SCORE_ALIENS[] = { 30,20,10 };
const int SCORE_UFO = 100;

//CONSTANTES DE JUEGO
constexpr int PLAYER_LIFES = 3;
constexpr int BUNKER_LIFES = 10;



class PlayState : public GameState{

public:
	//bucle de juego
	void Render() const override;
	void Update() override;
	void HandleEvent(const SDL_Event& ev) override;

	//constructor
	PlayState(Game* game,std::string fileName= MAP_PATH);

	//destructor
	~PlayState();
};






#endif // !PlayState_H__H_

