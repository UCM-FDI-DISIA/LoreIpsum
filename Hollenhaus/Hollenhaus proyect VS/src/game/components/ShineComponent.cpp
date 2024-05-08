#include <../pchs/pch.h>

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
	_mySpriteRenderers.push_back(entitySR); //aniade un nuevo SR al vector
	_fotoNueva.push_back(_newPic); // aniade una nueva textura al vector de estas (son las fotos con brillo)
	_fotosAntiguas.push_back(entitySR->getTexture()); // coge la foto inicial para devolversela cuando deje de brillar
}


void ShineComponent::Shine()
{
	
	
	
	
	//si detecta que el cursor esta encima
	if (_myBoxCollider->isCursorOver()) {

		//recorre todos los sprite renderers de las entidades que tenga que iluminar
		for (int i = 0; i < _mySpriteRenderers.size(); i++) {
		
			_mySpriteRenderers[i]->setTexture(_fotoNueva[i]); // a cada uno le asigna una nueva textura con la foto del brillito
		
		}
	}
	else {
		for (int i = 0; i < _mySpriteRenderers.size(); i++) {

			_mySpriteRenderers[i]->setTexture(_fotosAntiguas[i]); // si no está el cursor encima les devuelve a todas su aspecto original
		}
	}
	
	
}





