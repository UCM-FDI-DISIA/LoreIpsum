#pragma once
#include "ComponentUpdate.h"
#include "HandComponent.h"
#include "DeckComponent.h"


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

