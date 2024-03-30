#include "pch.h"
#include "Card.h"
#include <string>

#include "../Namespaces.h"
#include "../EffectCollection.h"

Card::Card() 
{

}

Card::Card(const Card& other) {

	cost = other.cost;
	value = other.value;
	sprite = other.sprite;
	unblockable = other.unblockable;
	cell = other.cell;


	ent_ = other.ent_;

	//effects = other.effects;

	/*
	for (auto& ef : other.effects) {
		EffectCollection::getEffect(
			e.type(),
			cardComp,
			e.value(),
			Effects::None
		)
	}
	*/

	//std::list<SDLEventCallback> effects;
}

Card::Card(int cost, int value) : cost(cost), value(value)
{
}

Card::Card(int cost, int value, std::string& sprite, bool unblockable)
	: cost(cost), value(value), sprite(sprite), unblockable(unblockable)
{
	
}

// mete en la lisa de efectos el efecto indicado
void Card::addCardEffect(SDLEventCallback effectCallback)
{
	// el efecto a hacer push back deberia ser un metodo especifico de la coleccion
	effects.push_back(effectCallback);
}
