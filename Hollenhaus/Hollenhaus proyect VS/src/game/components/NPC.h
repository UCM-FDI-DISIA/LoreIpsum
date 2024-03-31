#pragma once
#include "ComponentUpdate.h"

class BoxCollider;
class Factory;


class NPC : public ComponentUpdate
{
public:
	NPC(int scene);
	NPC(int scene, std::string name_);
	NPC(int scene, int t);
	NPC(int scene, int t, std::string name_);
	~NPC();

	void initComponent() override;
	void update() override;

	void OnLeftClickDown(int scene);
	void OnLeftClickUp();
	void reactToClick(int scene);
	void talkTo();
	void stoppedTalking();

private:
	int _id;
	int _scene;
	bool click;
	int type;
	bool talking;
	std::string name;
	
	BoxCollider* myBoxCollider;
	Factory* factory;
};