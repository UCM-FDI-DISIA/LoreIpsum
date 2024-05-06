#pragma once

//Checkml
#include <game/checkML.h>

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

	//----0: cancelar compra, 1: confimar compra, -1: no decidido.
	void setBuying(int state);
	int getBuying() { return buying; }

private:

	int index;
	int cardToPurchase;
	int buying = -1;

};

