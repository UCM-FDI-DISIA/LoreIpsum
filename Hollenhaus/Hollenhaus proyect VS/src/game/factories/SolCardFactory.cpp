#include "..\pchs\pch.h"
#include "SolCardFactory.h"


SolCardFactory::SolCardFactory()
{
}

SolCardFactory::~SolCardFactory()
{
}

ecs::entity_t SolCardFactory::CreateCard()
{

	ecs::entity_t newCard = Instantiate(Vector2D(0,0));




	return newCard;
}
