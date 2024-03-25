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
}

void ShineComponent::update()
{
	Shine();
}

void ShineComponent::Shine()
{
	_fotoantigua = _mySpriteRenderer->getTexture();

	if (_myBoxCollider->isCursorOver()) {
		_mySpriteRenderer->setTexture(_fotoNueva);
	}
	else {
		_mySpriteRenderer->setTexture(_fotoantigua);
	}
}





