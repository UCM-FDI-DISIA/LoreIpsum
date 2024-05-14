#include <../pchs/pch.h>

#include "Card.h"
#include <string>

#include "../Namespaces.h"
#include "../EffectCollection.h"

Card::Card() 
{

}

Card::Card(const Card& other) {
	id = other.id;
	cost = other.cost;
	value = other.value;
	sprite = other.sprite;
	unblockable = other.unblockable;
	cell = other.cell;

	//importante  no olvidarse de esto
	ent_ = other.ent_;

	//copiar los efectos bien
	for (auto& ef : other.effectsJSON) {

		if (ef.directions().empty())
			effects.push_back(
				EffectCollection::getEffect(
					ef.type(),
					this,
					ef.value(),
					Effects::None
				));
		else
			for (auto d : ef.directions())
				effects.push_back(
					EffectCollection::getEffect(
						ef.type(),
						this,
						ef.value(),
						d
					)
				);
	}

	effectsJSON = other.effectsJSON;
}

Card::Card(int id, int cost, int value, std::string& sprite, bool unblockable)
	: id(id), cost(cost), value(value), sprite(sprite), unblockable(unblockable)
{

}

// mete en la lisa de efectos el efecto indicado
void Card::addCardEffect(SDLEventCallback effectCallback)
{
	// el efecto a hacer push back deberia ser un metodo especifico de la coleccion
	effects.push_back(effectCallback);
}
