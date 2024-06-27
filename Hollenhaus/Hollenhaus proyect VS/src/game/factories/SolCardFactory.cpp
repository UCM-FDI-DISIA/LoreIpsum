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

ecs::entity_t SolCardFactory::CreateCard(int num, int tipo, bool bocabajo, Vector2D pos)
{
	//crear la carta
	ecs::entity_t newCard = Instantiate(pos, ecs::grp::SOLITAIRECARDS);

	//añadir componentes

	newCard->addComponent<SpriteRenderer>("solitaireCard");
	newCard->addComponent<BoxCollider>();

	//set layer && size
	newCard->setLayer(cardLayer);
	newCard->getComponent<Transform>()->setGlobalScale(cardScale.getX(),cardScale.getY());

	newCard->addComponent<SolCardComponent>(num, tipo, bocabajo, cardLayer);

	//hijos de la carta

	auto reverse = Instantiate(pos);
	reverse->addComponent<SpriteRenderer>("solitaireReverseCard");
	reverse->getComponent<Transform>()->setGlobalScale(reverseScale.getX(), reverseScale.getY());
	reverse->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	if (bocabajo) {
		reverse->setLayer(reverseLayer);
	}
	else { reverse->setLayer(0); }

	auto iconBig = Instantiate(pos + iconBigOffset); //icono grande
	iconBig->getComponent<Transform>()->setGlobalScale(iconBigScale.getX(), iconBigScale.getY());
	iconBig->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconBig->setLayer(iconsLayer);
	
	auto iconSmall = Instantiate(pos + iconSmallOffset); //icono pequenio
	iconSmall->getComponent<Transform>()->setGlobalScale(iconSmallScale.getX(), iconSmallScale.getY());
	iconSmall->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	iconSmall->setLayer(iconsLayer);

	switch (tipo)
	{
	case SolCardComponent::spades:
		iconSmall->addComponent<SpriteRenderer>("spades");
		iconBig->addComponent<SpriteRenderer>("spades");
		break;
	case SolCardComponent::clubs:
		iconSmall->addComponent<SpriteRenderer>("clubs");
		iconBig->addComponent<SpriteRenderer>("clubs");
		break;
	case SolCardComponent::hearts:
		iconSmall->addComponent<SpriteRenderer>("hearts");
		iconBig->addComponent<SpriteRenderer>("hearts");
		break;
	case SolCardComponent::diamonds:
		iconSmall->addComponent<SpriteRenderer>("diamonds");
		iconBig->addComponent<SpriteRenderer>("diamonds");
		break;
	}

	auto cardNumber = Instantiate(pos + numberOffset); //numero de la carta
	switch (tipo) {
	case SolCardComponent::spades:
		col = { 0, 0, 0 };
		break;
	case SolCardComponent::clubs:
		col = { 0, 0, 0 };
		break;
	case SolCardComponent::hearts:
		col = { 202, 7, 7 };
		break;
	case SolCardComponent::diamonds:
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
	cardNumber->getComponent<Transform>()->addParent(newCard->getComponent<Transform>());
	cardNumber->setLayer(iconsLayer);

	return newCard;
}
