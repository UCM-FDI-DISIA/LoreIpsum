#pragma once

#include <vector>

#include "ComponentUpdate.h"

class KeyManager :
    public ComponentUpdate
{
public:
    KeyManager();
    
    void initComponent() override;

    void addKey(std::string);

private:
    std::vector<std::string> descs_;
    std::vector<ecs::entity_t> images_;
    std::vector<std::string> imageIDs_;
};

