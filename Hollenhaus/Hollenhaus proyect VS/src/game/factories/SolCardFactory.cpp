#include "..\pchs\pch.h"
#include "../components/basics/TextComponent.h"
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
	//falta el componente de SolCardComponent


	//set layer && size
	newCard->setLayer(cardLayer);
	newCard->getComponent<Transform>()->setGlobalScale(cardScale.getX(),cardScale.getY());


	//hijos de la carta
	auto iconBig = Instantiate(iconBigOffset); //icono grande

	iconBig->addComponent<SpriteRenderer>("spades");
	iconBig->getComponent<Transform>()->setGlobalScale(iconBigScale.getX(), iconBigScale.getY());
	iconBig->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconBig->setLayer(iconsLayer);
	
	auto iconSmall = Instantiate(iconSmallOffset); //icono pequenio

	iconSmall->addComponent<SpriteRenderer>("spades");
	iconSmall->getComponent<Transform>()->setGlobalScale(iconSmallScale.getX(), iconSmallScale.getY());
	iconSmall->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconSmall->setLayer(iconsLayer);

	auto cardNumber = Instantiate(Vector2D(100, 550));
	cardNumber->addComponent<TextComponent>(std::to_string(money) + " DM", Fonts::GROTESK_32, SDL_Color({ Colors::MIDNIGHT_HOLLENHAUS }), 150, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	cardNumber->setLayer(10);

	return newCard;
}
