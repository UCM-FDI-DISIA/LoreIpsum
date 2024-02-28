#pragma once
#include "ComponentUpdate.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "GameStateMachine.h"
#include "BoxCollider.h"





class NPC : public ComponentUpdate
{
public:
	NPC();
	~NPC();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown();
	void OnLeftClickUP();
	void reactToClick();
private:
	int _id;
	bool click;
	
	BoxCollider* myBoxCollider;
};