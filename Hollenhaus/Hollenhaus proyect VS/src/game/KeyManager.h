#pragma once

#include "ComponentUpdate.h"

class Transform;
class Vector2D;

constexpr int N = 6;

class KeyManager :
    public ComponentUpdate
{
public:
    KeyManager();
    
    void initComponent() override;

    void addKey(std::string);

private:
    int addToY_;

    int lastKey_;

    std::vector<std::string> descs_;
    std::vector<ecs::entity_t> images_;
    std::vector<std::string> imageIDs_;

    Transform* tr_;
    Vector2D pos_;
};

