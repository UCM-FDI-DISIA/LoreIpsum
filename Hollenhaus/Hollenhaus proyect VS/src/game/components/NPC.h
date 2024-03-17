#pragma once
#include "ComponentUpdate.h"

class BoxCollider;

class NPC : public ComponentUpdate
{
public:
	NPC(int scene);
	NPC(int scene, int t);
	~NPC();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown(int scene);
	void OnLeftClickUp();
	void reactToClick(int scene);
	void talkTo();
private:
	int _id;
	int _scene;
	bool click;
	int type;
	
	BoxCollider* myBoxCollider;
};