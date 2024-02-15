#include "GameState.h"
#include "Manager.h"


GameState::GameState() 
{
}

//borra todas las entidades
GameState::~GameState()
{
}


//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la última iteración
void GameState::refresh()
{
    mngr->refresh();
}

void GameState::update()
{
    mngr->update();
}

void GameState::render()
{
    mngr->render();
}



