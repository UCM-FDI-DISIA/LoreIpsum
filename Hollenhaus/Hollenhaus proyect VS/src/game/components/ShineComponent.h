#pragma once

#include "ComponentUpdate.h"

class BoxCollider;
namespace ecs {
	using entity_t = Entity*;
}

class ShineComponent : public ComponentUpdate {

public: 
	ShineComponent(ecs::entity_t ent, std::string fotoNueva);
	~ShineComponent();

	void initComponent() override;
	void update() override;

	void Shine();

private:

	ecs::entity_t _entToShine;
	BoxCollider* _myBoxCollider;
	SpriteRenderer* _mySpriteRenderer;
	Texture* _fotoantigua;
	std::string _fotoNueva;

};