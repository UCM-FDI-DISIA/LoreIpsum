#include "pch.h"
#include "../checkML.h"
#include "ShineComponent.h"


ShineComponent::ShineComponent()
{
}

ShineComponent::~ShineComponent()
{
}

void ShineComponent::initComponent()
{
	_myBoxCollider = ent_->getComponent<BoxCollider>();
}

void ShineComponent::update()
{
	Shine();
}

void ShineComponent::addEnt(SpriteRenderer* entitySR, std::string _newPic)
{
	_mySpriteRenderers.push_back(entitySR);
	_fotoNueva.push_back(_newPic);
	_fotosAntiguas.push_back(entitySR->getTexture());
}


void ShineComponent::Shine()
{
	if (_myBoxCollider->isCursorOver()) {

		for (int i = 0; i < _mySpriteRenderers.size(); i++) {
		
			_mySpriteRenderers[i]->setTexture(_fotoNueva[i]);
		
		}
	}
	else {
		for (int i = 0; i < _mySpriteRenderers.size(); i++) {

			_mySpriteRenderers[i]->setTexture(_fotosAntiguas[i]);
		}
	}
	
}





