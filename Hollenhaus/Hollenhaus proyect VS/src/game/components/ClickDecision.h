#pragma once
#include "ComponentUpdate.h"

#include "managers/Manager.h"
#include "basics/BoxCollider.h"

class ClickDecision :
    public ComponentUpdate
{
public:
    ClickDecision(int decision);
    ~ClickDecision(){}

	void initComponent() override;
	void update() override;

    void OnLeftClickDown();
    void OnLeftClickUp();

    void TakeDecision();

private:

    int decision_;
    bool click_;

    BoxCollider* collider_;
};

