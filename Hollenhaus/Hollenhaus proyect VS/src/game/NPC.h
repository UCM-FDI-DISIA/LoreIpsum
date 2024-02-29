#pragma once
#include "ComponentUpdate.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "GameStateMachine.h"
#include "BoxCollider.h"





class NPC : public ComponentUpdate
{
public:
	NPC(int scene);
	~NPC();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown(int scene);
	void reactToClick(int scene);
private:
	int _id;
	int _scene;
	bool click;
	
	BoxCollider* myBoxCollider;
};