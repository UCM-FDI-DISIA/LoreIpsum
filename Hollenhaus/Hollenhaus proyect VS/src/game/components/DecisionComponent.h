#pragma once
#include "../components/ComponentUpdate.h"

class DecisionComponent : public ComponentUpdate
{
public:
	//----Constructora:
	DecisionComponent();
	//----Destructora:
	~DecisionComponent();

	void initComponent() override;

	void setDecision(int i);

	void manageDecisions();

	void setCardToPurchase(int i);
	void resetCardToPurchase();
	int getCardToPurchase() { return cardToPurchase; }

	void setBuying(bool buy);
	bool getBuying() { return buying; }

private:

	int index;
	int cardToPurchase;
	bool buying = false;

};

