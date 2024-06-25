#include "..\pchs\pch.h"
#include "SolCardFactory.h"

//#include <game/components/basics/SpriteRenderer.h>

SolCardFactory::SolCardFactory()
{
}

SolCardFactory::~SolCardFactory()
{
}

ecs::entity_t SolCardFactory::CreateCard()
{
	//crear la carta
	ecs::entity_t newCard = Instantiate(Vector2D(0,0));

	//añadir componentes
	newCard->addComponent<SpriteRenderer>("solitaireCard");
	newCard->addComponent<BoxCollider>();
	newCard->addComponent<SpriteRenderer>("solitaireCard");


	//set layer && size
	newCard->setLayer(cardLayer);
	newCard->getComponent<Transform>()->setGlobalScale(cardScale.getX(),cardScale.getY());



	//crear los hijos de la carta
	auto iconBig = Instantiate(iconBigOffset);

	iconBig->addComponent<SpriteRenderer>("spades");
	iconBig->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconBig->setLayer(iconsLayer);


	return newCard;
}
