#include "GameState.h"
#include "Manager.h"

#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"

GameState::GameState() 
{
    
    
    /*
    auto mngr = GameStateMachine::instance()->getMngr();
    
    auto entityPrueba = mngr->addEntity();
    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
    auto componentPrueba = mngr->addComponent<Transform>(entityPrueba);
    std::cout << ((mngr->getComponent<Transform>(entityPrueba)) != nullptr) << std::endl;
    //auto componentPrueba2 = mngr->addComponent<SpriteRenderer>(entityPrueba, "hola");
    std::cout << ((mngr->hasComponent<Transform>(entityPrueba))) << std::endl;
    std::cout << ((mngr->hasComponent<SpriteRenderer>(entityPrueba))) << std::endl;
    */
    
    

    //ih().insertFunction(0, [this] {PruebaInput(); });

    //ih().insertFunction(InputHandler::MOUSE_LEFT_CLICK, [this] {PruebaInput(); });
    //ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK, [this] {PruebaInput(); });
}

//borra todas las entidades
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

void GameState::render()
{
    GameStateMachine::instance()->getMngr()->render();
}

