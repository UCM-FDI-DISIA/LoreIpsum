#pragma once

//Checkml
#include "ComponentUpdate.h"
#include <game/checkML.h>

class SolCardComponent : public ComponentUpdate
{
public:

	SolCardComponent();
	SolCardComponent(int, int, bool); 
	~SolCardComponent();

	void initComponent() override;

	void update() override;

	// enum de tipo (palo)
	enum tipo { spades, clubs, hearts, diamonds };
	
private:
	
	// numero de la carta (1-13)
	int number;


	tipo myType;

	//si esta bocabajo o no
	bool bocabajo = false;


};

