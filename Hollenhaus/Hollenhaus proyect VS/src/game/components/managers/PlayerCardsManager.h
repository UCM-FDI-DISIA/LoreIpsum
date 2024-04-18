#pragma once
#include "../ComponentUpdate.h"
#include "../HandComponent.h"
#include "../DeckComponent.h"

constexpr int MAX_IN_HAND = 6;

class PlayerCardsManager :
	public ComponentUpdate
{
private:
	HandComponent* hand_;
	DeckComponent* deck_;

public:
	PlayerCardsManager(HandComponent* hand, DeckComponent* deck) : hand_(hand), deck_(deck)
	{
	}

	~PlayerCardsManager() override;

	void drawCard();

	void initComponent() override;

	//necesario para la IA
	HandComponent* getHand();
};
