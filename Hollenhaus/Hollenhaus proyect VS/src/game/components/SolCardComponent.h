#pragma once

//Checkml
#include "ComponentUpdate.h"
#include <game/checkML.h>

class SolCardComponent : public ComponentUpdate
{
public:

	SolCardComponent();
	SolCardComponent(int, int, bool, int); 
	~SolCardComponent();

	void initComponent() override;

	void update() override;

	// enum de tipo (palo)
	enum tipo { spades, clubs, hearts, diamonds };

	//getters
	bool getFaceDown() { return bocabajo; };

	SolCardComponent* getCardOnTop() { return cardOnTop; };
	void setCardOnTop(SolCardComponent* newCardOnTop) 
	{ 
		cardOnTop = newCardOnTop; 
	};
	
	SolCardComponent* getCardOnBottom() { return cardOnBottom; };
	void setCardOnBottom(SolCardComponent* newCardOnBottom)
	{ 
		cardOnBottom = newCardOnBottom;
	};

	int getNumber() { return number; };

	tipo getTipo() { return myType; };

	Vector2D getOffset() { return cardOnTopOffset; };

	int getLayer() { return mainLayer; };
	void setLayer(int newLayer);
	
private:
	
	Vector2D cardOnTopOffset = Vector2D(0, 30);

	tipo myType; // variable de tipo tipo

	// numero de la carta (1-13)
	int number;

	//si esta bocabajo o no
	bool bocabajo = false;

	SolCardComponent* cardOnTop = nullptr; // puntero a si tiene una carta encima 

	SolCardComponent* cardOnBottom = nullptr; // puntero a la carta de detras 

	int mainLayer;

};

