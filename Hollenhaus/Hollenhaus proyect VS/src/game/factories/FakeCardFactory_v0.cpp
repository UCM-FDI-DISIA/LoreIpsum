#include <../pchs/pch.h>

#include "FakeCardFactory_v0.h"
#include "../components/basics/TextComponent.h"
#include "../EffectCollection.h"
#include "../Namespaces.h"

ecs::entity_t FakeCardFactory_v0::createFakeCard(int id, Vector2D pos, int cost, int value, std::string& sprite, bool unblockable, std::vector<JsonData::CardEffect>& effects)
{
    ecs::entity_t fakeCard = Instantiate(pos, ecs::grp::CARDS);
    fakeCard->addComponent<Transform>();
    fakeCard->addComponent<SpriteRenderer>("card");
    fakeCard->addComponent<BoxCollider>();
    fakeCard->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	fakeCard->getComponent<Transform>()->setGlobalScale(cardScale, cardScale);
	fakeCard->getComponent<Transform>()->setGlobalPos(pos);
    fakeCard->addComponent<Card>( id, cost, value, sprite, unblockable );
	Card* cardComp = fakeCard->getComponent<Card>();

	fakeCard->setLayer(2);

	addEffects(cardComp, effects);
	addValueCostTexts(fakeCard, value, cost);
	addEffectsImages(fakeCard, effects);
	return fakeCard;
}

void FakeCardFactory_v0::addValueCostTexts(ecs::entity_t card, int value, int cost)
{
	ecs::entity_t textoValor = Instantiate(Vector2D(0, 0));
	auto posX = 8;


	// Texto blanco para el valor
	textoValor->addComponent<TextComponent>(std::to_string(value), 
		Fonts::GROTESK_16, Colors::PEARL_HOLLENHAUS, 10,
		Text::CenterCenter, Text::Center);

	textoValor->getComponent<Transform>()->addParent(card->getComponent<Transform>());
	textoValor->getComponent<Transform>()->getRelativePos().set(posX, 88);
	textoValor->setLayer(card->getLastLayer());


	ecs::entity_t textoCoste = Instantiate(Vector2D(0, 0));
	// Texto amarillo para el coste
	textoCoste->addComponent<TextComponent>(std::to_string(cost), 
		Fonts::GROTESK_16, Colors::AMARILLO_PIS, 10,
		Text::CenterCenter, Text::Center);

	textoCoste->getComponent<Transform>()->addParent(card->getComponent<Transform>());
	textoCoste->getComponent<Transform>()->getRelativePos().set(posX, 10);
	//textoCoste->getComponent<Transform>()->setGlobalScale(10, 10); // esta linea aporta 0 porque es una fuente
	//textoCoste->getComponent<Transform>()->getRelativeScale().set(10, 10);

	textoCoste->setLayer(card->getLastLayer());
}

void FakeCardFactory_v0::addEffectsImages(ecs::entity_t card, std::vector<JsonData::CardEffect>& effects)
{
	int initialX = 15;
	int initialY = 55;
	int offSetX = 25;
	int offSetY = 15;
	int nCols = 2;
	int layer = 10;
	float scale = effects.size() == 1 ? 0.08 : 0.045;

	ecs::entity_t effectImage;

	std::vector<std::string> efectsIdsNames{ "esquina", "centro", "flecha", "superflecha", "block", "unblockable" };
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

			auto color = Colors::TEAL_MIKU;

			if (effects[i].value() < 0)
				color = Colors::ROJO_HOLLENHAUS;
			else
				color = Colors::BAHIA_BENEFICIO;

			auto textEntity = Instantiate(Vector2D());
			auto textTrans = textEntity->getComponent<Transform>();
			textEntity->setLayer(effectImage->getLayer());
			textTrans->addParent(effectImage->getComponent<Transform>());
			auto textPos = Vector2D(23, 8);
			textTrans->setRelativePos(textPos);
			textEntity->addComponent<TextComponent>(valueText, 
				Fonts::GROTESK_18, color, 100);
			/*auto valueChange = effectImage->addComponent<TextComponent>(valueText, 
				Fonts::GROTESK_16, color, 100);*/
			
		}
	}
}

void FakeCardFactory_v0::addEffects(Card* cardComp, std::vector<JsonData::CardEffect>& effects)
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