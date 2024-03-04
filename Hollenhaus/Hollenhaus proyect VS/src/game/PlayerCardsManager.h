#pragma once
#include "ComponentUpdate.h"
#include "HandComponent.h"
#include "DeckComponent.h"

const int MAX_IN_HAND = 6;

class PlayerCardsManager :
    public ComponentUpdate
{
private:
    HandComponent* hand_;
    DeckComponent* deck_;


public:
    PlayerCardsManager(HandComponent* hand, DeckComponent* deck) :hand_(hand), deck_(deck) {}
    ~PlayerCardsManager() {}

    void drawCard();

    void initComponent() override;

};

