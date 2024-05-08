#include <../pchs/pch.h>

#include "../Namespaces.h"
#include "CardFactory_v1.h"

#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/BoxCollider.h"
#include "../components/DeckComponent.h"
#include "../components/managers/PlayerCardsManager.h"
#include "../components/managers/CardStateManager.h"
#include "../components/basics/TextComponent.h"

#include "../EffectCollection.h"
#include "../gamestates/GameState.h"
#include "game/components/ShineComponent.h"


ecs::entity_t CardFactory_v1::createCard(int id, Vector2D pos, int cost, int value, std::string& sprite,
                                         bool unblockable,
                                         std::vector<JsonData::CardEffect>& effects, bool bocarriba)
{
	ecs::entity_t card = Instantiate(pos, ecs::grp::CARDS);

	card->addComponent<SpriteRenderer>(sprite);
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();

	auto cardTransform = card->getComponent<Transform>();
	cardTransform->setGlobalScale(cardScale, cardScale);

	auto cardCardStateManager = card->getComponent<CardStateManager>();
	cardCardStateManager->setState(Cards::ON_DECK);

	card->addComponent<Card>(
		id, cost, value, sprite, unblockable
	);

	addInfo(card, cost, value, effects, !bocarriba);

	addShadow(0,0,1, card->getComponent<Transform>());

	if (!bocarriba)
		addDeckImageChild(card);

	return card;
}


//crea la mano del jugador
ecs::entity_t CardFactory_v1::createHand()
{
	int initY = 465;
	int initX = 360;
	int offSetX = 50;

	Vector2D deckPos(initX, initY);
	ecs::entity_t hand = Instantiate(deckPos);
	hand->addComponent<HandComponent>()->setOwner(Players::PLAYER1);

	return hand;
}

//crea la mano del rival
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

	auto maze = GameStateMachine::instance()->getCurrentState()->getMazeWithPos();

	for (auto c : maze)
	{
		if (c.first > -1)
		{
			auto card = sdlutils().cards().at(std::to_string(c.first));
			// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
			ecs::entity_t ent = createCard(
				card.id(),
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
	}
	addDeckImage(initX, initY);
	addDeckShadow(initX, initY);

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

	//añadir las cartas al mazo
	for (int i = 0; i < cardsOnDeck; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i));
		// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		ecs::entity_t ent = createCard(
			card.id(),
			Vector2D(initX, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects(),
			false
		);
		ent->setLayer(1);
		deck->getComponent<DeckComponent>()->addCartToDeck(ent->getComponent<Card>());
	}

	//las añadimos otra vez para asegurar que el enemigo tenga cartas de sobra
	for (int i = 0; i < cardsOnDeck; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i));
		// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		ecs::entity_t ent = createCard(
			card.id(),
			Vector2D(initX, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects(),
			false
		);
		ent->setLayer(1);
		deck->getComponent<DeckComponent>()->addCartToDeck(ent->getComponent<Card>());
	}

	addDeckImage(initX, initY, true);
	TuVieja("Deck2");
	addDeckShadow(initX, initY);

	return deck;
}

ecs::entity_t CardFactory_v1::createDeckJ2Multiplayer()
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

	auto maze = GameStateMachine::instance()->getCurrentState()->getMazeRival();

	for (auto c : maze)
	{
		auto card = sdlutils().cards().at(std::to_string(c));
		// importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		ecs::entity_t ent = createCard(
			card.id(),
			Vector2D(initX, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects(),
			false
		);
		ent->setLayer(1);
		deck->getComponent<DeckComponent>()->addCartToDeck(ent->getComponent<Card>());
	}


	addDeckImage(initX, initY, true);
	addDeckShadow(initX, initY);
	TuVieja("Deck2");

	return deck;
}

void CardFactory_v1::addInfo(ecs::entity_t card, int cost, int value, std::vector<JsonData::CardEffect>& effects,
                             bool bocabajo)
{
	addEffects(card->getComponent<Card>(), effects);
	addValueCostTexts(card, value, cost);
	addEffectsImages(card, effects, bocabajo);
}

void CardFactory_v1::addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects, bool rival)
{
	int initialX = 15;
	int initialY = 55;
	int offSetX = 25;
	int offSetY = 15;
	int nCols = 2;
	int layer = 10;
	float scale = effects.size() == 1 ? 0.08 : 0.045;

	ecs::entity_t effectImage;

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

		effectImage->setLayer(card->getLastLayer());


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
			std::string valueText = effects[i].value() < 0 ? "" : "+";
			valueText = valueText + std::to_string(effects[i].value());

			auto color = Colors::PEARL_HOLLENHAUS;


			if (effects[i].value() < 0)
			{
				if (!rival)
					color = Colors::ROJO_HOLLENHAUS;
				else
					color = Colors::NARANJA_PERJUICIO;
			}
			else
			{
				if (!rival)
					color = Colors::BAHIA_BENEFICIO;
				else
					color = Colors::VERDE_BENEFICIO;
			}

			auto valueChange = effectImage->addComponent<TextComponent>(valueText,
			                                                            Fonts::GROTESK_18, color, 100);
			valueChange->setOffset(25, 20);
		}
	}
}

void CardFactory_v1::addValueCostTexts(ecs::entity_t card, int value, int cost)
{
	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));
	auto posX = 10;

	// Texto blanco para el valor
	textoValor->addComponent<TextComponent>(std::to_string(value), Fonts::GROTESK_16,
	                                        Colors::PEARL_HOLLENHAUS, 100,
	                                        Text::CenterCenter, Text::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());
	textoValor->getComponent<Transform>()->getRelativePos().set(posX, 104);
	textoValor->setLayer(card->getLastLayer());


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));
	// Texto amarillo para el coste
	textoCoste->addComponent<TextComponent>(std::to_string(cost), Fonts::GROTESK_16,
	                                        Colors::AMARILLO_PIS, 100,
	                                        Text::CenterCenter, Text::Center);
	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());
	textoCoste->getComponent<Transform>()->getRelativePos().set(posX, 11);
	textoCoste->getComponent<Transform>()->setGlobalScale(10, 10); // esta linea aporta 0 porque es una fuente
	//textoCoste->getComponent<Transform>()->getRelativeScale().set(10, 10);


	textoCoste->setLayer(card->getLastLayer());
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

	//MUY IMPORTANTEEEEEEEE!!!!!!!!!
	cardComp->setEffectsJSON(effects);
}

void CardFactory_v1::addDeckImage(int initX, int initY, bool opposite)
{
	auto deckImage = Instantiate(Vector2D(initX - 5, initY - 5));
	deckImage->addComponent<SpriteRenderer>("reverseCard");
	deckImage->getComponent<Transform>()->setGlobalScale(Vector2D(0.65f, 0.65f));

	if (opposite)
		deckImage->getComponent<Transform>()->setGlobalAngle(180.0f);
	else
	{
		deckImage->addComponent<BoxCollider>()->setAnchoredToSprite(true);
		deckImage->addComponent<ShineComponent>();
		deckImage->getComponent<ShineComponent>()->addEnt(deckImage->getComponent<SpriteRenderer>(),
		                                                  "reverseCard_brilli");
	}

	deckImage->setLayer(100);
}

void CardFactory_v1::addDeckImageChild(ecs::entity_t card)
{
	auto cardTrans = card->getComponent<Transform>();
	auto deckImage = Instantiate(Vector2D(cardTrans->getGlobalPos()));

	deckImage->getComponent<Transform>()->addParent(cardTrans);
	deckImage->getComponent<Transform>()->setGlobalScale(Vector2D(0.55f, 0.55f));
	//if (opposite)
	deckImage->getComponent<Transform>()->setGlobalAngle(180.0f);
	deckImage->addComponent<SpriteRenderer>("reverseCard");
	/*deckImage->addComponent<BoxCollider>()->setAnchoredToSprite(true);
	deckImage->addComponent<ShineComponent>();
	deckImage->getComponent<ShineComponent>()->addEnt(deckImage->getComponent<SpriteRenderer>(), "reverseCard_brilli");
	*/deckImage->setLayer(card->getLastLayer() + 1);
}

void CardFactory_v1::addDeckShadow(int x, int y, int layer)
{
	auto sombra = Instantiate(Vector2D());
	auto trans = sombra->getComponent<Transform>();
	trans->setGlobalPos(x - 15, y - 15);
	trans->setGlobalScale(Vector2D(0.65, 0.65));
	sombra->addComponent<SpriteRenderer>("deck_sombra");
	sombra->setLayer(layer);
}

void CardFactory_v1::addShadow(int x, int y, int layer, Transform* parent)
{
	auto shadow = Instantiate(Vector2D(x, y));
	auto newPos = parent->getGlobalPos();
	shadow->getComponent<Transform>()->setGlobalPos(newPos.getX() + 4, newPos.getY() + 4);
	shadow->getComponent<Transform>()->setRelativePos(0,0);
	shadow->addComponent<SpriteRenderer>("card_sombra");
	shadow->getComponent<Transform>()->addParent(parent);
	shadow->setLayer(layer);
}
