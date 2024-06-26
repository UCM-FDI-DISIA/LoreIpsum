#include "..\pchs\pch.h"
#include "../components/basics/TextComponent.h"
#include "../components/SolCardComponent.h"
#include "SolCardFactory.h"

//#include <game/components/basics/SpriteRenderer.h>

SolCardFactory::SolCardFactory()
{
}

SolCardFactory::~SolCardFactory()
{
}

ecs::entity_t SolCardFactory::CreateCard(int num, int tipo, bool bocabajo)
{
	//crear la carta
	ecs::entity_t newCard = Instantiate(Vector2D(0,0));

	//añadir componentes

	newCard->addComponent<SpriteRenderer>("solitaireCard");
	newCard->addComponent<BoxCollider>();
	newCard->addComponent<SolCardComponent>();


	//set layer && size
	newCard->setLayer(cardLayer);
	newCard->getComponent<Transform>()->setGlobalScale(cardScale.getX(),cardScale.getY());


	//hijos de la carta

	auto reverse = Instantiate();
	reverse->addComponent<SpriteRenderer>("solitaireReverseCard");
	reverse->getComponent<Transform>()->setGlobalScale(reverseScale.getX(), reverseScale.getY());
	reverse->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	if (bocabajo) {
		reverse->setLayer(reverseLayer);
	}
	else { reverse->setLayer(0); }

	auto iconBig = Instantiate(iconBigOffset); //icono grande
	switch (tipo)
	{
		case 0:
		iconBig->addComponent<SpriteRenderer>("spades");
		break;
		case 1:
		iconBig->addComponent<SpriteRenderer>("clubs");
		break;
		case 2:
		iconBig->addComponent<SpriteRenderer>("hearts");
		break;
		case 3:
		iconBig->addComponent<SpriteRenderer>("diamonds");
		break;
	}
	iconBig->getComponent<Transform>()->setGlobalScale(iconBigScale.getX(), iconBigScale.getY());
	iconBig->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconBig->setLayer(iconsLayer);
	
	auto iconSmall = Instantiate(iconSmallOffset); //icono pequenio

	switch (tipo)
	{
	case 0:
		iconSmall->addComponent<SpriteRenderer>("spades");
		break;
	case 1:
		iconSmall->addComponent<SpriteRenderer>("clubs");
		break;
	case 2:
		iconSmall->addComponent<SpriteRenderer>("hearts");
		break;
	case 3:
		iconSmall->addComponent<SpriteRenderer>("diamonds");
		break;
	}
	iconSmall->getComponent<Transform>()->setGlobalScale(iconSmallScale.getX(), iconSmallScale.getY());
	iconSmall->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconSmall->setLayer(iconsLayer);

	auto cardNumber = Instantiate(numberOffset); //numero de la carta
	switch (tipo) {
	case 0:
		col = { 0, 0, 0 };
		break;
	case 1:
		col = { 0, 0, 0 };
		break;
	case 2:
		col = { 202, 7, 7 };
		break;
	case 3:
		col = { 202, 7, 7 };
		break;
	}

	switch (num) {
	case 0:
		textoCarta = "A";
		break;
	case 11:
		textoCarta = "J";
		break;
	case 12:
		textoCarta = "Q";
		break;
	case 13:
		textoCarta = "K";
		break;
	default:
		textoCarta = std::to_string(num);
		break;
	}
	cardNumber->addComponent<TextComponent>(textoCarta, Fonts::GROTESK_32, col, 20, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	cardNumber->setLayer(iconsLayer);

	return newCard;
}
