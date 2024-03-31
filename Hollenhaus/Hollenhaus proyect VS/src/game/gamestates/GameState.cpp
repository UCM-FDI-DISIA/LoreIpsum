#include "pch.h"
#include "GameState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../../sdlutils/InputHandler.h"
#include "../GameStateMachine.h"
#include "../Data.h"

// DECLARAR LAS VARIABLES ESTATICAS
Data* GameState::data = nullptr;

// borra todas las entidades
GameState::~GameState()
{
    GameStateMachine::instance()->getMngr()->Free();
}

//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la última iteración
void GameState::refresh()
{
    GameStateMachine::instance()->getMngr()->refresh();
}

void GameState::update()
{
    GameStateMachine::instance()->getMngr()->update();
}

void GameState::render() const 
{
    GameStateMachine::instance()->getMngr()->render();
}

void GameState::setWinnerOnData(int w)
{
    data->setWinner(w);
}

void GameState::setLastPaulPos(Vector2D paulPos)
{
    data->SetCityPos(paulPos);
}

// para acceder al drawer del data desde el estado
std::array<int, CARDS_IN_GAME> GameState::getDrawer()
{
    return data->GetDrawer();
}

// para acceder al mazo del data desde el estado
std::unordered_map<int,Vector2D> GameState::getMaze()
{
    return data->GetMaze();
}

Vector2D GameState::getLastPaulPos()
{
    return data->getLastPaulPos();
}

// para settear el mazo del data desde el estado
void GameState::setMaze(std::list<int> mazeToSave, std::list<Vector2D> MazePosToSave)
{
    data->SetNewMaze(mazeToSave, MazePosToSave);
}

// para settear el drawer del data desde el estado
void GameState::setDrawer(std::array<int, 50> drawerToSave)
{
    data->SetNewDrawer(drawerToSave);
}

void GameState::saveData()
{
    // sobreescribe el archivo de guardado
    data->Write();
}

void GameState::loadData()
{
    // lee el archivo de guardado
    data->Read();
}

void GameState::setData(Data* _data)
{
    data = _data;
}