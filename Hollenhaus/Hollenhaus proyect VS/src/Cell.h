#pragma once

#include "Card.h"

enum Owner
{
	NONE,
	PLAYER1,
	PLAYER2,
	NULO
};

enum Direction
{
	Arriba,
	Derecha,
	Abajo,
	Izquierda
};

class Cell
{
	bool active; // si en la celda se pueden jugar cartas o no
	int totalValue; // puntuacion con los efectos aplicados
	Owner player; // a que jugador pertenece
	Card* card; // carta posicionada en esta celda
	std::vector<Cell*> adjacents; // punteros a las celdas adyacentes en cruz (arriba, abajo, izq, der)
	std::string effectHistory;
	// falta effect history/effect list
public:
	Cell();
	Cell(Cell& cell); // ctor. por copia
	Cell(Card* card, Owner);
	~Cell();

	void addEffect(std::string);
	void initAdjacents(); // sets pointers to adjacents
	void addTotal(int add);

	// getters
	bool getActive() const { return active; }
	Owner getPlayer() const{ return player; }
	Card* getCard() const { return card; }
	std::string getEffectHistory() { return effectHistory; }
	int getTotalValue() { return totalValue; }
	bool isCorner() { return true; }
	bool isCenter() { return true; }

	// setters
	void setActive(bool v) { active = v; }
	void setPlayer(Owner o) { player = o; }
	void setCard(Card* c) { card = c; }
	void setCard(Card* c, Owner o);
	void deleteCard() const { delete card; } // ???

	Cell& operator=(const Cell& o)
	{
		// delete current list in data;
		// deep copy o.data to data here;
		return *this;
	}
};
