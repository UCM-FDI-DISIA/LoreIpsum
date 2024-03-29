#include "pch.h"
#include "CardFactory_v1.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/BoxCollider.h"
#include "../components/DeckComponent.h"
#include "../components/managers/PlayerCardsManager.h"
#include "../components/managers/CardStateManager.h"
#include "../EffectCollection.h"
#include "../Namespaces.h"
#include "../components/basics/TextComponent.h"


ecs::entity_t CardFactory_v1::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable,
                                         std::vector<JsonData::CardEffect>& effects, bool bocarriba)
{
	ecs::entity_t card = Instantiate(pos, ecs::grp::CARDS);

	if (!bocarriba)
		sprite = "reverseCard";

	card->addComponent<SpriteRenderer>(sprite);
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();

	auto cardTransform = card->getComponent<Transform>();
	cardTransform->setGlobalScale(cardScale, cardScale);

	auto cardCardStateManager = card->getComponent<CardStateManager>();
	cardCardStateManager->setState(Cards::ON_DECK);

	card->addComponent<Card>(
		cost, value, sprite, unblockable
	);

	addInfo(card, cost, value, effects);

	return card;
}


ecs::entity_t CardFactory_v1::createHand()
{
	int initY = 470;
	int initX = 320;
	int offSetX = 50;

	Vector2D deckPos(initX, initY);
	ecs::entity_t hand = Instantiate(deckPos);
	hand->addComponent<HandComponent>()->setOwner(Players::PLAYER1);

	return hand;
}

ecs::entity_t CardFactory_v1::createHandJ2()
{
	int initX = 320;
	int initY = -39;

	Vector2D deckPos(initX, initY);
	ecs::entity_t hand = Instantiate(deckPos);
	hand->addComponent<HandComponent>()->setUpwards();
	hand->getComponent<HandComponent>()->setOwner(Players::PLAYER2);

	return hand;
}

void CardFactory_v1::addInfo(ecs::entity_t card, int cost, int value, std::vector<JsonData::CardEffect>& effects)
{
	addEffects(card->getComponent<Card>(), effects);
	addValueCostTexts(card, value, cost);
	addEffectsImages(card, effects);
}

ecs::entity_t CardFactory_v1::createDeck()
{
	int initY = 475;
	int initX = 600;

	ecs::entity_t hand = createHand();

	Vector2D deckPos(initX, initY);

	ecs::entity_t deck = Instantiate(deckPos);
	deck->addComponent<BoxCollider>()->setPosOffset(Vector2D(-15, 0));
	deck->addComponent<DeckComponent>();
	deck->addComponent<PlayerCardsManager>(
		hand->getComponent<HandComponent>(),
		deck->getComponent<DeckComponent>()
	);
	deck->setLayer(2);
	deck->getComponent<DeckComponent>()->setOwner(Players::PLAYER1);

	for (int i = 0; i < cardsOnDeck; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i));
		// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		ecs::entity_t ent = createCard(
			Vector2D(initX, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects()
		);
		ent->setLayer(1);
		deck->getComponent<DeckComponent>()->addCartToDeck(ent->getComponent<Card>());
	}
	addDeckImage(initX, initY);
	TuVieja("Deck1");

	return deck;
}

ecs::entity_t CardFactory_v1::createDeckJ2()
{
	int initX = 600;
	int initY = -12;

	ecs::entity_t hand = createHandJ2();

	Vector2D deckPos(initX, initY);

	ecs::entity_t deck = Instantiate(deckPos);
	deck->addComponent<BoxCollider>()->setPosOffset(Vector2D(-15, 0));
	deck->addComponent<DeckComponent>()->setOwner(Players::PLAYER2);
	deck->addComponent<PlayerCardsManager>(
		hand->getComponent<HandComponent>(),
		deck->getComponent<DeckComponent>()
	);
	deck->setLayer(2);

	//instantie

	for (int i = 0; i < cardsOnDeck; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i));
		// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		ecs::entity_t ent = createCard(
			Vector2D(initX, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects()
		);
		ent->setLayer(1);
		if (deck->getComponent<DeckComponent>()->getOwner() == Players::PLAYER2)
			ent->getComponent<Transform>()->setGlobalAngle(180.0f);
		deck->getComponent<DeckComponent>()->addCartToDeck(ent->getComponent<Card>());
	}
	addDeckImage(initX, initY, true);
	TuVieja("Deck2");

	return deck;
}


void CardFactory_v1::addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects)
{
	int initialX = 15;
	int initialY = 55;
	int offSetX = 25;
	int offSetY = 15;
	int nCols = 2;
	int layer = 10;
	float scale = effects.size() == 1 ? 0.078 : 0.045;

	ecs::entity_t effectImage;
	ecs::entity_t valueChange;

	std::vector<std::string> efectsIdsNames{"esquina", "centro", "flecha", "superflecha", "block", "unblockable"};
	std::string efectID;


	for (int i = 0; i < effects.size(); i++)
	{
		effectImage = Instantiate(Vector2D(0, 0));

		efectID = efectsIdsNames[effects[i].type()];

		effectImage->addComponent<SpriteRenderer>(efectID);


		effectImage->getComponent<Transform>()->addParent(card->getComponent<Transform>());

		effectImage->getComponent<Transform>()->setGlobalScale(scale, scale);
		Vector2D gpos(initialX + ((i % nCols) * offSetX), initialY + ((i / nCols) * offSetY));

		effectImage->getComponent<Transform>()->getRelativePos().set(gpos);

		effectImage->setLayer(layer);


		//si es una flecha, girarla
		if (effects[i].type() >= Effects::Flecha && effects[i].type() <= Effects::Block)
		{
			Effects::Direction dir = effects[i].directions()[0];
			effectImage->getComponent<Transform>()->getGlobalAngle() =
				dir == Effects::Right ? 90.f : dir == Effects::Down ? 180.f : dir == Effects::Left ? 270 : 0;
		}

		//poner el simbolo del valor
		if (effects[i].value() != 0)
		{
			std::string valueText = effects[i].value() < 0 ? "-" : "+";
			valueText = valueText + std::to_string(effects[i].value());

			valueChange = Instantiate(Vector2D(0, 0));

			valueChange->addComponent<TextComponent>(valueText, "8bit_16pt", SDL_Color({200,50,200, 255}), 100);

			valueChange->getComponent<Transform>()->addParent(effectImage->getComponent<Transform>());
			valueChange->getComponent<Transform>()->getRelativePos().set(-5, 0);

			valueChange->setLayer(layer + 1);
		}
	}
}

void CardFactory_v1::addValueCostTexts(ecs::entity_t card, int value, int cost)
{
	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));

	textoValor->addComponent<TextComponent>(std::to_string(value), "8bit_24pt", SDL_Color({255, 255, 255, 255}), 100,
	                                        Text::CenterCenter, Text::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoValor->getComponent<Transform>()->getRelativePos().set(10, 102);

	textoValor->setLayer(100);


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));

	textoCoste->addComponent<TextComponent>(std::to_string(cost), "8bit_24pt", SDL_Color({255, 255, 255, 255}), 100,
	                                        Text::CenterCenter, Text::Center);

	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoCoste->getComponent<Transform>()->getRelativePos().set(10, 10);
	textoCoste->getComponent<Transform>()->setGlobalScale(10, 10); // esta linea aporta 0 porque es una fuente
	//textoCoste->getComponent<Transform>()->getRelativeScale().set(10, 10);


	textoCoste->setLayer(100);
}

void CardFactory_v1::addEffects(Card* cardComp, std::vector<JsonData::CardEffect>& effects)
{
	for (auto e : effects)
	{
		if (e.directions().empty())
			cardComp->addCardEffect(
				EffectCollection::getEffect(
					e.type(),
					cardComp,
					e.value(),
					Effects::None
				)
			);
		else
			for (auto d : e.directions())
				cardComp->addCardEffect(
					EffectCollection::getEffect(
						e.type(),
						cardComp,
						e.value(),
						d
					)
				);
	}
}

void CardFactory_v1::addDeckImage(int initX, int initY, bool opposite)
{
	auto deckImage = Instantiate(Vector2D(initX, initY));

	deckImage->getComponent<Transform>()->setGlobalScale(Vector2D(0.7f, 0.7f));
	if (opposite)
		deckImage->getComponent<Transform>()->setGlobalAngle(180.0f);
	deckImage->addComponent<SpriteRenderer>("reverseCard");

	deckImage->setLayer(100);
}
