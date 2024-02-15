#include "GameState.h"
#include "Manager.h"

#include "../Transform.h"
#include "../SpriteRenderer.h"
GameState::GameState() 
{
    mngr = new ecs::Manager();
    auto entityPrueba = mngr->addEntity();
    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
    auto componentPrueba = mngr->addComponent<Transform>(entityPrueba);
    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
    //auto componentPrueba2 = mngr->addComponent<SpriteRenderer>(entityPrueba, "hola");
    std::cout << ((mngr->hasComponent<Transform>(entityPrueba))) << std::endl;
    std::cout << ((mngr->hasComponent<SpriteRenderer>(entityPrueba))) << std::endl;

}

//borra todas las entidades
GameState::~GameState()
{
}


//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la �ltima iteraci�n
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



