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
	case 1:
		textoCarta = "A";
		break;
	case 10:
		textoCarta = " ";
		number10Execption(tipo, pos, newCard); // como el 10 no cabe he hecho este metodo que pone una foto de un 10 con el color adecuado
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

ecs::entity_t SolCardFactory::CreateCardByIndex(int index, bool bocabajo, Vector2D pos)
{
	return CreateCard(index%13+1,index/13,bocabajo,pos);
}

ecs::entity_t SolCardFactory::CreateCasillaDcha(int tipo, Vector2D pos)
{
	ecs::entity_t newCasilla = Instantiate(pos, ecs::grp::SOLITAIRERIGHTCELL);

	newCasilla->addComponent<BoxCollider>();

	newCasilla->getComponent<Transform>()->setGlobalScale(0.7, 1);

	newCasilla->addComponent<SolCardComponent>(0, tipo, false, cardLayer);


	return newCasilla;
}

void SolCardFactory::createCardsBoard(std::vector<int> indices)
{
	std::vector<SolCardComponent*> cardsCmps(52);

	auto posAct = startPosCardsOnBoard;

	int layerAct = 0;

	for (int i = 0; i < 15; i++) {

		if ((i == 0 || i == 2 || i == 5 || i == 9 || i == 14)) {
			cardsCmps[i] = CreateCardByIndex(indices[i],false, posAct)->getComponent<SolCardComponent>();
			cardsCmps[i]->setLayer(layerAct);

			posAct = Vector2D(posAct.getX() + boardCardsOffsetX, startPosCardsOnBoard.getY());

			layerAct = 0;
		}
		else {
			cardsCmps[i] = CreateCardByIndex(indices[i], true, posAct)->getComponent<SolCardComponent>();
			cardsCmps[i]->setLayer(layerAct);

			posAct = Vector2D(posAct.getX() , posAct.getY() + boardCardsOffsetY);

			layerAct += 2;
		}
	}

	setCardsReferences(cardsCmps, 0, 0);
	setCardsReferences(cardsCmps, 1, 2);
	setCardsReferences(cardsCmps, 3, 5);
	setCardsReferences(cardsCmps, 6, 9);
	setCardsReferences(cardsCmps, 10, 14);

	for (int j = 15; j < 52; j++) {

		cardsCmps[j] = CreateCardByIndex(indices[j], true, Vector2D(15,20))->getComponent<SolCardComponent>();
		cardsCmps[j]->setLayer(layerAct);

		posAct = Vector2D(posAct.getX(), posAct.getY() + boardCardsOffsetY);

		cardsCmps[j]->setLeftDeck(true);

		layerAct += 2;
	}
	
}

void SolCardFactory::number10Execption(int tipo, Vector2D pos, ecs::entity_t card)
{
	auto num = Instantiate(Vector2D(pos.getX() + 6, pos.getY() + 6)); 
	num->getComponent<Transform>()->setGlobalScale(iconSmallScale.getX() + 0.3, iconSmallScale.getY() + 0.3);
	num->getComponent<Transform>()->addParent(card->getComponent<Transform>());
	num->setLayer(iconsLayer);
	if (tipo == SolCardComponent::clubs || tipo == SolCardComponent::spades) {
		num->addComponent<SpriteRenderer>("black10");
	}
	else {
		num->addComponent<SpriteRenderer>("red10");
	}
}

void SolCardFactory::setCardsReferences(std::vector<SolCardComponent*>& cards, int ini, int fin)
{

	if (ini >= fin) return;

	for (int i = ini; i < fin; i++) {
		cards[i]->setCardOnTop(cards[i+1]);
		cards[i+1]->setCardOnBottom(cards[i]);
	}
}
