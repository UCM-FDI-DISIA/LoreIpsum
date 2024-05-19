#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"

class BoxCollider;
class Factory;
class Transform;


class NPC : public ComponentUpdate
{
public:
	enum Type
	{
		BUTTON,
		TALKING
	};

	NPC(int scene, int t = BUTTON, std::string name_ = "", int id = 0, int convo = 0, bool = true, bool = true);
	~NPC() override;

	void initComponent() override;
	void update() override;

	void OnLeftClickDown(int scene, bool = true, bool = true);
	void OnLeftClickUp();
	void reactToClick(int scene, bool = true, bool = true);
	void talkTo();
	void stoppedTalking();
	void nextConvo();
	int getID() { return _id; }

private:
	int _id;
	int _scene;
	bool click;
	int type;
	int convo_;
	bool talking;
	std::string name;
	ecs::entity_t npcDialogue;

	float pos;
	bool closeToPaul; //si esta cerca de Paul, podra hablar, si no, no
	
	BoxCollider* myBoxCollider;
	Factory* factory;
	Transform* myTransform; //para saber si estamos cerca de Paul o no
};