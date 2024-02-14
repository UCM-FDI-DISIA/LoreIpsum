#include "GameState.h"

// reserva suficiente (?) memoria para evitar el redimensionamiento
// del vector de entidades
GameState::GameState() : ents_()
{
    ents_.reserve(100);
}

//borra todas las entidades
GameState::~GameState()
{
    for (auto e : ents_) {
        delete e;
    }
}

Entity* GameState::addEntity()
{
    Entity* e = new Entity(this);   // crea la entidad
    e->setAlive(true);              // inicializa la entidad
    ents_.push_back(e);             // se a�ade a la lista de entidades

    return e;
}

//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la �ltima iteraci�n
void GameState::refresh()
{
    ents_.erase(
        //Para cada elemento de ents_, remove_if llama a la funci�n
        //(lambda expression) para decider si borrarlo o no, aprovechamos
        //para liberar la memoria tambi�n
        std::remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
            if (e->isAlive()) {
                return false;
            }
            else {
                delete e;
                return true;
            }
            }),
        ents_.end());
}

void GameState::update()
{
    auto n = ents_.size();
    for (auto i = 0u; i < n; i++)
        ents_[i]->update();
}

void GameState::render()
{
    auto n = ents_.size();
    for (auto i = 0u; i < n; i++)
        ents_[i]->render();
}
