#include "Manager.h"


namespace ecs {

// reserva suficiente (?) memoria para evitar el redimensionamiento
// del vector de entidades
Manager::Manager() : ents_()
{
    ents_.reserve(100);
}

//borra todas las entidades
Manager::~Manager()
{
    for (auto e : ents_) {
        delete e;
    }
}

Entity* Manager::addEntity()
{
    Entity* e = new Entity(nullptr);   // crea la entidad
    e->setAlive(true);              // inicializa la entidad
    ents_.push_back(e);             // se añade a la lista de entidades

    return e;
}

//Su objetivo es borrar todas las entidades muertas, es
//decir las que han salido del juego en la última iteración
void Manager::refresh()
{
    ents_.erase(
        //Para cada elemento de ents_, remove_if llama a la función
        //(lambda expression) para decider si borrarlo o no, aprovechamos
        //para liberar la memoria también
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

void Manager::update()
{
    auto n = ents_.size();
    for (auto i = 0u; i < n; i++)
        ents_[i]->update();
}

void Manager::render()
{
    auto n = ents_.size();
    for (auto i = 0u; i < n; i++)
        ents_[i]->render();
}

}
