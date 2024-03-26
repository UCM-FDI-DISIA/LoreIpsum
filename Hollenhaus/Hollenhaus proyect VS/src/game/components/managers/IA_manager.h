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

	void evaluateState();
private:


	/// reaplica todos los efectos
	//void applyAllEffects();
	//void updateScore();
};






