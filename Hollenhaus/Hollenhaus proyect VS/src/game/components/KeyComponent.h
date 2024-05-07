#pragma once

//Checkml
#include <game/checkML.h>

#include <vector>
#include <string>

#include "ComponentRender.h"

class Transform;
class SpriteRenderer;
class Vector2D;

constexpr int TOTAL_KEYS = 6;

class KeyComponent :
    public ComponentRender
{
public:
    KeyComponent(const int keys);

    void initComponent() override;

private:
    void set();

    int addToY_;

    int NKeys_;

    // Vector de nombres de iconos
    std::vector<std::string> keyNames_;
    // Vector de descripciones
    std::vector<std::string> descs_;
    // Vector de entidades icono + desc, 1. Imagen / 2. Texto
    std::vector<std::pair<ecs::entity_t, ecs::entity_t>> keys_;

    Transform* tr_;
    SpriteRenderer* sr_;

    Vector2D pos_,
        firstOffset_,
        secondOffset_;

    float bookWidth_;

    std::string font_;
};

