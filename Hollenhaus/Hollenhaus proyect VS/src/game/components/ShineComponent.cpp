#include "pch.h"
#include "../checkML.h"
#include "ShineComponent.h"


ShineComponent::ShineComponent(ecs::entity_t ent, std::string fotoNueva)
{
	_entToShine = ent;
	_fotoNueva = fotoNueva;
}

ShineComponent::~ShineComponent()
{
}

void ShineComponent::initComponent()
{
    _myBoxCollider = ent_->getComponent<BoxCollider>();
	_mySpriteRenderer = _entToShine->getComponent<SpriteRenderer>();
	_fotoantigua = _mySpriteRenderer->getTexture();
}

void ShineComponent::update()
{
	if (_myBoxCollider->isCursorOver()) {

		Shine();
		
	}
	else {
		_mySpriteRenderer->setTexture(_fotoantigua);
	}
}

void ShineComponent::Shine()
{
	_mySpriteRenderer->setTexture(_fotoNueva);
	
}





