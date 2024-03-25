#pragma once

#include "../ComponentUpdate.h"

class Card;

class IA_manager : public ComponentUpdate
{
public:
	IA_manager();
	~IA_manager();

	void initComponent() override;

	void update() override;

private:

	void evaluateState();

	/// reaplica todos los efectos
	//void applyAllEffects();
	//void updateScore();
};

/*
class State {
	std::vector<std::vector<Card*>> _board;

	std::vector<Card*> playerHand;
	std::vector<Card*> enemyHand;

	std::vector<Card*> playerDeck;
	std::vector<Card*> enemyDeck;

	int actionPoints;

	TuplaSolucion();

};
*/