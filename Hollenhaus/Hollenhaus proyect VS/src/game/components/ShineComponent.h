#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include <vector>

class BoxCollider;
namespace ecs {
	using entity_t = Entity*;
}

class ShineComponent : public ComponentUpdate {

public: 
	ShineComponent();
	~ShineComponent()override;

	void initComponent() override;
	void update() override;

	void addEnt(SpriteRenderer* entitySR, std::string _newPic);
	void Shine();

	void setShine();
	void outShine();

private:

	BoxCollider* _myBoxCollider; // box collider de la entidad a la que se le aniade el componente

	ecs::entity_t _entToShine; // esta es la entidad que va a brillar (se hace una lista de todas ellas)

	std::vector<SpriteRenderer*> _mySpriteRenderers; //vector de sprite renderers de entidades que brillan

	std::vector<Texture*> _fotosAntiguas; //vector de texturas de fotos iniciales de entidades que brillan

	std::vector<std::string> _fotoNueva; // el textID de foto con brillos

};