#include "pch.h"
#include "DecisionComponent.h"

DecisionComponent::DecisionComponent()
{

}

DecisionComponent::~DecisionComponent()
{

}

void DecisionComponent::initComponent()
{
	cardToPurchase = -1;
}

void DecisionComponent::setDecision(int i)
{
	index = i;

}

void DecisionComponent::manageDecisions()
{
	switch (index)
	{
	case 1:


		break;
	case 2:

		break;

	default:
		break;
	}

}

void DecisionComponent::setCardToPurchase(int i)
{
	cardToPurchase = i;
}

void DecisionComponent::resetCardToPurchase()
{
	cardToPurchase = -1;
}

void DecisionComponent::setBuying(bool buy)
{
	buying = buy;
}
