#pragma once
#include "../ComponentUpdate.h"
#include <vector>
#include <list>
#include <functional>
#include "../../Namespaces.h"

#include "IA_manager.h" //intentar cambiarlo para quitarlo de aqui


namespace ecs {
    class Entity;
    using entity_t = Entity*;
}

class TutorialManager : public ComponentUpdate
{
public:
    TutorialManager();
    ~TutorialManager() override;

private:


};
