#pragma once

#include <vector>
#include <string>

#include "../ComponentUpdate.h"

class Transform;
class Vector2D;

constexpr int NUMBER_OF_KEYS = 6;

class KeyManager :
    public ComponentUpdate
{
public:
    KeyManager();
    
    void initComponent() override;

    void addKey();

private:
    int addToY_;

    int lastKey_;

    std::vector<std::string> keyNames_;
    std::vector<std::string> descs_;
    std::vector<std::pair<ecs::entity_t, ecs::entity_t>> keys_; // 1. Imagen / 2. Texto

    Transform* tr_;
    Vector2D pos_;

    std::string font_;
};

