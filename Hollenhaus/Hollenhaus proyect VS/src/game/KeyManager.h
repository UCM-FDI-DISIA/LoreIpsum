#pragma once

#include <vector>

#include "ComponentUpdate.h"
#include "SpriteRenderer.h"

class KeyManager :
    public ComponentUpdate
{
public:
    KeyManager();
    
    void initComponent() override;

private:
    std::vector<std::string> descs_;
    std::vector<ecs::entity_t> images_;
    std::vector<std::string> imageIDs_;
};

