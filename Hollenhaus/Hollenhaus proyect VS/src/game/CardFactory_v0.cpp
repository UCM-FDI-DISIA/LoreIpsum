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

#include "TextComponent.h"


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

#pragma region Valor y coste



	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));

	textoValor->addComponent<TextComponent>(std::to_string(value), "8bit_size_12", SDL_Color({255, 255, 255, 255}), TextComponent::Alignment::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoValor->getComponent<Transform>()->getRelativePos().set(10, 87);

	textoValor->setLayer(10);


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));

	textoCoste->addComponent<TextComponent>(std::to_string(cost), "8bit_size_12", SDL_Color({ 255, 255, 255, 255 }), TextComponent::Alignment::Center);

	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoCoste->getComponent<Transform>()->getRelativePos().set(10, 10);

	textoCoste->setLayer(10);

#pragma endregion


#pragma region Imanfenes de efecto

	int initialX = 15;
	int initialY = 55;
	int offSetX = 20;
	int offSetY = 15;
	int nCols = 2;
	int layer = 10;
	float scale = 0.045;

	ecs::entity_t effectImage;


	std::vector<std::string> efectsIdsNames{ "esquina" ,"centro","flecha" ,"superflecha" ,"block" , "unblockable" };
	std::string efectID;

	


	for (int i = 0; i < effects.size(); i++) {

		effectImage = Instantiate(Vector2D(0, 0));

		efectID = efectsIdsNames[effects[i].type()];

		effectImage->addComponent<SpriteRenderer>(efectID);
	

		effectImage->getComponent<Transform>()->addParent(card->getComponent<Transform>());

		//effectImage->getComponent<Transform>()->getGlobalScale().set(1, 1);
		effectImage->getComponent<Transform>()->getRelativeScale().set(scale, scale);
		Vector2D gpos(initialX + ((i%nCols) *offSetX), initialY + ((i/nCols)*offSetY) );

		effectImage->getComponent<Transform>()->getRelativePos().set(gpos);

		effectImage->setLayer(layer);
	}


#pragma endregion


	return card;
}


/*
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
*/

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
