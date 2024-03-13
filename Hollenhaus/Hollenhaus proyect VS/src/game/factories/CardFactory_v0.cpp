#include "pch.h"
#include "CardFactory_v0.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/BoxCollider.h"
#include "../components/Drag.h"
#include "../components/managers/CardStateManager.h"
#include "../components/DropDetector.h"
#include "../components/Cell.h"
#include "../EffectCollection.h"
#include "../Enums.h"
#include "../components/basics/TextComponent.h"


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
	cardCardStateManager->setState(CardStateManager::ON_DECK);

	const auto cardComp = card->addComponent<Card>(
		cost, value, sprite, unblockable
	);


	/// Hemos creado getEffect para evitar:
	// [this, card] { EffectCollection::addAdj(card->getComponent<Card>()->getCell(), 
	// Down, 20, false);}
	/// Al metodo createCard se le deberia pasar el array de effects
	///	y a continuacion iterar sobre el, anyadiendole a la carta cada
	///	efecto tal que:
	/*cardComp->addCardEffect(
		EffectCollection::getEffect(
			Effects::Flecha,
			cardComp,
			20,
			Effects::Down
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
					Effects::None
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



	addValueCostTexts(card, value, cost);

	addEffectsImages(card, effects);


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

ecs::entity_t CardFactory_v0::createHand()
{
	int initY = 470;
	int initX = 270;
	int offSetX = 50;

	// todavia no se como saber cards.size() de otra manera
	/*int size = 0;
	for (auto c : cards) esto no funciona porque no esta definido begin y end
		size++;*/

	for (int i = 0; i < cardsOnHand; i++)
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

	ecs::entity_t hand = Instantiate();

	hand->addComponent<Transform>();
	Vector2D deckPos(initX, initY);
	hand->getComponent<Transform>()->setGlobalPos(deckPos);
	//hand->addComponent<HandComponent>();
	return hand;
}

void CardFactory_v0::addEffectsImages(ecs::entity_t card, std::vector<SDLUtils::CardEffect>& effects)
{

	int initialX = 15;
	int initialY = 55;
	int offSetX = 25;
	int offSetY = 15;
	int nCols = 2;
	int layer = 10;
	float scale = effects.size() == 1 ? 0.075 : 0.045;

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
			
			Effects::Direction dir = effects[i].directions()[0];
			effectImage->getComponent<Transform>()->getGlobalAngle() = 
				 dir == Effects::Right ?  90.f :  dir == Effects::Down ? 180.f : dir == Effects::Left ? 270 : 0;
		}


		/// WIP: flecha de la habilidad bloqueo
		///	No borrar de momento
		//if (effects[i].type() == Effects::Block)
		//{ // ha de instanciar otra imagen flecha apuntando hacia donde bloquea
		//	auto arrowImage = Instantiate(Vector2D(0, 0));
		//	arrowImage->addComponent<SpriteRenderer>(efectsIdsNames[Effects::Flecha]);

		//	arrowImage->getComponent<Transform>()->addParent(effectImage->getComponent<Transform>());
		//	arrowImage->getComponent<Transform>()->getRelativeScale().set(scale, scale);
		//	Vector2D gpos(0, 0);
		//	arrowImage->getComponent<Transform>()->getRelativePos().set(gpos);
		//	arrowImage->setLayer(layer);

		//	Effects::Direction dir = effects[i].directions()[0];
		//	arrowImage->getComponent<Transform>()->getGlobalAngle() = 
		//		 dir == Effects::Right ?  90.f :  dir == Effects::Down ? 180.f : dir == Effects::Left ? 270 : 0;
		//}


		if (effects[i].value() != 0) {

			std::string valueText = effects[i].value() < 0 ? "-" : "+";
			valueText = valueText + std::to_string(effects[i].value());

			valueChange = Instantiate(Vector2D(0,0));

			valueChange->addComponent<TextComponent>(valueText, "8bit_8pt", SDL_Color({0, 0, 0, 255}), 100);

			valueChange->getComponent<Transform>()->addParent(effectImage->getComponent<Transform>());
			valueChange->getComponent<Transform>()->getRelativePos().set(-5, 0);

			valueChange->setLayer(layer + 1);
		}
	}


}

void CardFactory_v0::addValueCostTexts(ecs::entity_t card,  int value, int cost)
{
	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));

	textoValor->addComponent<TextComponent>(std::to_string(value), "8bit_size_12", SDL_Color({ 255, 255, 255, 255 }), 100,Text::BoxPivotPoint::CenterCenter,Text::TextAlignment::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoValor->getComponent<Transform>()->getRelativePos().set(10, 87);

	textoValor->setLayer(100);


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));

	textoCoste->addComponent<TextComponent>(std::to_string(cost), "8bit_size_12", SDL_Color({ 255, 255, 255, 255 }),100, Text::BoxPivotPoint::CenterCenter,Text::TextAlignment::Center);

	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());

	textoCoste->getComponent<Transform>()->getRelativePos().set(10, 10);
	textoCoste->getComponent<Transform>()->getRelativeScale().set(10, 10);

	textoCoste->setLayer(100);
}
