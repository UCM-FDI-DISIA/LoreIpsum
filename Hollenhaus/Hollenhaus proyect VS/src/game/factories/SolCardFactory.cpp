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

	ecs::entity_t newCard = Instantiate(Vector2D(0,0));

	newCard->addComponent<SpriteRenderer>("solitaireCard");

	newCard->setLayer(2);


	newCard->getComponent<Transform>()->setGlobalScale(1,1);

	auto icon = Instantiate(Vector2D(3,35));

	icon->addComponent<SpriteRenderer>("spades");
	icon->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	icon->setLayer(3);




	return newCard;
}
