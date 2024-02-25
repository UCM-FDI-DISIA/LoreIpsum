#include "Card.h"
#include <string>



Card::Card() 
{
}

Card::Card(int cost, int value) : cost(cost), value(value)
{
}

Card::Card(int cost, int value, std::string& sprite) 
	: cost(cost), value(value), sprite(sprite)
{
}


void Card::addCardEffect(SDLEventCallback effectCallback)
{
	// el efecto a hacer push back deberia ser un metodo especifico de la coleccion
	cardEffectCallbacks.push_back(effectCallback);
}
