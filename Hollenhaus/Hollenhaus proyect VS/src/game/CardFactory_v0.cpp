#include "CardFactory_v0.h"
#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"

#include "DropDetector.h"
#include "../Cell.h"
#include "../EffectCollection.h"


ecs::entity_t CardFactory_v0::createCard(Vector2D pos, int cost, int value, std::string& sprite, bool unblockable,
                                         std::vector<SDLUtils::CardEffect>& effects)
{
	ecs::entity_t card = Instantiate(pos, ecs::grp::CARDS);

	card->addComponent<SpriteRenderer>(sprite);
	card->addComponent<BoxCollider>();
	card->addComponent<CardStateManager>();

	auto cardTransform = card->getComponent<Transform>();
	cardTransform->getGlobalScale().set(cardScale, cardScale);

	auto cardCardStateManager = card->getComponent<CardStateManager>();
	cardCardStateManager->setState(CardStateManager::ON_HAND);

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

	/// Bucle de carga de efectos a carta
	for (const auto& e : effects)
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
		else for (const auto d : e.directions())
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

	return card;
}


ecs::entity_t CardFactory_v0::createDropDetector(Vector2D pos)
{
	ecs::entity_t dropDect = Instantiate(ecs::grp::DROPS);

	dropDect->addComponent<Transform>()->getGlobalPos().set(pos);
	dropDect->addComponent<BoxCollider>();
	dropDect->addComponent<DropDetector>()->getCardPos().set(pos);

	dropDect->getComponent<BoxCollider>()->setSize(
		Vector2D(sdlutils().images().at("card").width() * cardScale,
		         (sdlutils().images().at("card").height()) * cardScale));

	//dropDect->addComponent<Cell>();


	return dropDect;
}

ecs::entity_t CardFactory_v0::createDropDetector_v2(Vector2D pos)
{
	ecs::entity_t dropDect = Instantiate(ecs::grp::DROPS);

	dropDect->addComponent<Transform>()->getGlobalPos().set(pos);
	dropDect->addComponent<BoxCollider>();
	dropDect->addComponent<DropDetector>()->getCardPos().set(pos);

	dropDect->getComponent<BoxCollider>()->setSize(
		Vector2D(sdlutils().images().at("card").width() * cardScale,
		         (sdlutils().images().at("card").height()) * cardScale));

	//dropDect->addComponent<Cell>();


	return dropDect;
}

ecs::entity_t CardFactory_v0::createBoard()
{
	float initX = 200;
	float initY = 20;
	float xOffset = 82;
	float yOffset = 120;


	createDropDetector(Vector2D(initX, initY));
	createDropDetector(Vector2D(initX + xOffset, initY));
	createDropDetector(Vector2D(initX + (2 * xOffset), initY));


	createDropDetector(Vector2D(initX, initY + yOffset));
	createDropDetector(Vector2D(initX + xOffset, initY + yOffset));
	createDropDetector(Vector2D(initX + (2 * xOffset), initY + yOffset));


	createDropDetector(Vector2D(initX, initY + (2 * yOffset)));
	createDropDetector(Vector2D(initX + xOffset, initY + (2 * yOffset)));
	createDropDetector(Vector2D(initX + (2 * xOffset), initY + (2 * yOffset)));


	return nullptr;
}

void CardFactory_v0::createHand()
{
	int initY = 470;
	int initX = 270;
	int offSetX = 50;

	// todavia no se como saber cards.size() de otra manera
	/*int size = 0;
	for (auto c : cards) esto no funciona porque no esta definido begin y end
		size++;*/

	for (int i = 0; i < 6; i++)
	{ 
		auto card = sdlutils().cards().at(std::to_string(i)); // importantisimo que en el resources.json los ids sean "0", "1"... es ridiculo e ineficiente pero simplifica
		createCard(
			Vector2D(initX + offSetX * i, initY),
			card.cost(),
			card.value(),
			card.sprite(),
			card.unblockable(),
			card.effects()
		)->setLayer(1);
	}


	// Cartas ejemplo
	/*createCard(Vector2D(initX, initY), 2, 2, sprite, true)->setLayer(1);
	createCard(Vector2D(initX + offSetX, initY),3,3,sprite, false)->setLayer(1);
	createCard(Vector2D(initX + offSetX*2, initY), 4, 4, sprite, false)->setLayer(1);
	createCard(Vector2D(initX + offSetX*3, initY), 5, 5, sprite, false)->setLayer(2);*/
}
