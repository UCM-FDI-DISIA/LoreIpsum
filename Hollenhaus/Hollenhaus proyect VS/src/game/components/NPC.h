#pragma once
#include "ComponentUpdate.h"

class BoxCollider;
class Factory;
class Transform;


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
	ecs::entity_t npcDialogue;

	float pos;
	bool closeToPaul; //si esta cerca de Paul, podra hablar, si no, no
	
	BoxCollider* myBoxCollider;
	Factory* factory;
	Transform* myTransform; //para saber si estamos cerca de Paul o no

	//para destruir el dialogo si estamos lejos de paul

};