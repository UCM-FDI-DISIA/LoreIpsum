#include "CardFactory_v1.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "DeckComponent.h"
#include "PlayerCardsManager.h"
#include "Drag.h"
#include "CardStateManager.h"

#include "DropDetector.h"
#include "../Cell.h"
#include "../EffectCollection.h"

#include "TextComponent.h"


ecs::entity_t CardFactory_v1::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable,
	std::vector<SDLUtils::CardEffect>& effects)
{

	ecs::entity_t card = Instantiate(pos, ecs::grp::CARDS);

	card->addComponent<SpriteRenderer>(sprite);
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();

	auto cardTransform = card->getComponent<Transform>();
	cardTransform->getGlobalScale().set(cardScale, cardScale);

	auto cardCardStateManager = card->getComponent<CardStateManager>();
	cardCardStateManager->setState(CardStateManager::ON_DECK);

	const auto cardComp = card->addComponent<Card>(
		cost, value, sprite, unblockable
		);


	/// Hemos creado getEffect para evitar:
	// [this, card] { EffectCollection::addAdj(card->getComponent<Card>()->getCell(), CellData::Down, 20, false);}
	/// Al metodo createCard se le deberia pasar el array de effects
	///	y a continuacion iterar sobre el, anyadiendole a la carta cada
	///	efecto tal que:
	/*cardComp->addCardEffect(
		EffectCollection::getEffect(
			Effects::Flecha,
			cardComp,
			20,
			CellData::Down
		)
	);*/

	/// WIP: bucle de carga de efectos a carta
	for (auto e : effects)
	{
		if (e.directions().empty())
			cardComp->addCardEffect(
				EffectCollection::getEffect(
					e.type(),
					cardComp,
					e.value(),
					CellData::None
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

	/*
	auto cardDrag = mngr().getComponent<Drag>(card);
	cardDrag->addCondition([card]() {
		auto state = mngr().getComponent<CardStateManager>(card)->getState();
		return state == CardStateManager::ON_HAND;
	});
	*/



	addValueCostTexts(card, value, cost);

	addEffectsImages(card, effects);


	return card;
}


ecs::entity_t CardFactory_v1::createHand()
{
	int initY = 470;
	int initX = 320;
	int offSetX = 50;

	ecs::entity_t hand = Instantiate();

	hand->addComponent<Transform>();
	Vector2D deckPos(initX, initY);
	hand->getComponent<Transform>()->setGlobalPos(deckPos);
	hand->addComponent<HandComponent>();


	return hand;

	// todavia no se como saber cards.size() de otra manera
	/*int size = 0;
	for (auto c : cards) esto no funciona porque no esta definido begin y end
		size++;*/

	


	// Cartas ejemplo
	/*createCard(Vector2D(initX, initY), 2, 2, sprite, true)->setLayer(1);
	createCard(Vector2D(initX + offSetX, initY),3,3,sprite, false)->setLayer(1);
	createCard(Vector2D(initX + offSetX*2, initY), 4, 4, sprite, false)->setLayer(1);
	createCard(Vector2D(initX + offSetX*3, initY), 5, 5, sprite, false)->setLayer(2);*/
}

void CardFactory_v1::createDeck() {

	int initY = 500;
	int initX = 600;

	ecs::entity_t hand = createHand();

	ecs::entity_t deck = Instantiate();
	deck->addComponent<Transform>();
	Vector2D deckPos(initX, initY);
	deck->getComponent<Transform>()->setGlobalPos(deckPos);
	deck->addComponent<BoxCollider>();
	deck->addComponent<DeckComponent>();
	deck->addComponent<PlayerCardsManager>(
		hand->getComponent<HandComponent>(),
		deck->getComponent<DeckComponent>()
	);
	deck->setLayer(2);

	//instantie

	for (int i = 0; i < 6; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i)); // importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
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

	TuVieja("Deck1");

}

ecs::entity_t CardFactory_v1::createHandJ2()
{
	ecs::entity_t hand = Instantiate();

	int initX = 320;
	int initY = 20;

	hand->addComponent<Transform>();
	Vector2D deckPos(initX, initY);
	hand->getComponent<Transform>()->setGlobalPos(deckPos);
	//hand->getComponent<Transform>()->setGlobalAngle(180.0f); // esto peta
	hand->addComponent<HandComponent>()->setUpwards();

	return hand;
}

void CardFactory_v1::createDeckJ2()
{
	int initX = 600;
	int initY = 1;

	ecs::entity_t hand = createHandJ2();

	ecs::entity_t deck = Instantiate();
	deck->addComponent<Transform>();
	Vector2D deckPos(initX, initY);
	deck->getComponent<Transform>()->setGlobalPos(deckPos);
	//deck->getComponent<Transform>()->setGlobalAngle(180.0f); // esto peta
	deck->addComponent<BoxCollider>();
	deck->addComponent<DeckComponent>();
	deck->addComponent<PlayerCardsManager>(
		hand->getComponent<HandComponent>(),
		deck->getComponent<DeckComponent>()
	);
	deck->setLayer(2);

	//instantie

	for (int i = 0; i < 6; i++)
	{
		auto card = sdlutils().cards().at(std::to_string(i)); // importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
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

	TuVieja("Deck2");
}


void CardFactory_v1::addEffectsImages(ecs::entity_t card, std::vector<SDLUtils::CardEffect>& effects)
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

	std::vector<std::string> efectsIdsNames{ "esquina" ,"centro","flecha" ,"superflecha" ,"block" , "unblockable" };
	std::string efectID;



	for (int i = 0; i < effects.size(); i++) {

		effectImage = Instantiate(Vector2D(0, 0));

		efectID = efectsIdsNames[effects[i].type()];

		effectImage->addComponent<SpriteRenderer>(efectID);


		effectImage->getComponent<Transform>()->addParent(card->getComponent<Transform>());

		//effectImage->getComponent<Transform>()->getGlobalScale().set(1, 1);
		effectImage->getComponent<Transform>()->getRelativeScale().set(scale, scale);
		Vector2D gpos(initialX + ((i % nCols) * offSetX), initialY + ((i / nCols) * offSetY));

		effectImage->getComponent<Transform>()->getRelativePos().set(gpos);

		effectImage->setLayer(layer);



		if (effects[i].type() >= 2 && effects[i].type() <= 4) {

			CellData::Direction dir = effects[i].directions()[0];
			effectImage->getComponent<Transform>()->getGlobalAngle() =
				dir == CellData::Right ? 90.f : dir == CellData::Down ? 180.f : dir == CellData::Left ? 270 : 0;
		}



		if (effects[i].value() != 0) {

			std::string valueText = effects[i].value() < 0 ? "-" : "+";
			valueText = valueText + std::to_string(effects[i].value());

			valueChange = Instantiate(Vector2D(0, 0));

			valueChange->addComponent<TextComponent>(valueText, "8bit_8pt", SDL_Color({ 0, 0, 0, 255 }), 100);

			valueChange->getComponent<Transform>()->addParent(effectImage->getComponent<Transform>());
			valueChange->getComponent<Transform>()->getRelativePos().set(-5, 0);

			valueChange->setLayer(layer + 1);
		}
	}


}

void CardFactory_v1::addValueCostTexts(ecs::entity_t card, int value, int cost)
{
	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));

	textoValor->addComponent<TextComponent>(std::to_string(value), "8bit_size_12", SDL_Color({ 255, 255, 255, 255 }), 100, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoValor->getComponent<Transform>()->getRelativePos().set(10, 87);

	textoValor->setLayer(100);


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));

	textoCoste->addComponent<TextComponent>(std::to_string(cost), "8bit_size_12", SDL_Color({ 255, 255, 255, 255 }), 100, TextComponent::BoxPivotPoint::CenterCenter, TextComponent::TextAlignment::Center);

	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoCoste->getComponent<Transform>()->getRelativePos().set(10, 10);
	textoCoste->getComponent<Transform>()->getRelativeScale().set(10, 10);

	textoCoste->setLayer(100);
}