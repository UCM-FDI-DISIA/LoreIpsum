#pragma once

#include <vector>
//#include "../game/Card.h"
#include "game/Card.h"
#include <functional>

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void(void)>;

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
	bool corner; // si la celda es esquina de tablero o no
	bool center; // si la celda es centro de trablero o no
	int totalValue; // puntuacion con los efectos aplicados
	Owner player; // a que jugador pertenece
	Card* card; // carta posicionada en esta celda
	std::string effectHistory;
	std::array<Cell*, 4> adjacents; // punteros a las celdas adyacentes en cruz (arriba, abajo, izq, der)
	std::list<SDLEventCallback> effectCallbacks; // lista de los efectos que tiene una celda concreta
	std::list<SDLEventCallback>::iterator listIT;


	void emit() const;

public:
	Cell();
	Cell(Cell& cell); // ctor. por copia
	Cell(Card* card, Owner);
	~Cell();

	void addEffect(SDLEventCallback effectCallback);
	void applyValue(Card* card);
	void addTotal(int add);

	// getters
	bool getActive() const { return active; }
	bool getCorner() const { return corner; }
	bool getCenter() const { return center; }
	int getTotalValue() const { return totalValue; }
	Owner getPlayer() const{ 
		player;
		return player; 
	
	}
	Card* getCard() const { return card; }
	std::string& getEffectHistory() { return effectHistory; }
	std::array<Cell*, 4>& getAdjacents() { return adjacents; } // sets pointers to adjacent
	std::list<SDLEventCallback> getEffects() const { return effectCallbacks; }

	// setters
	void setActive(bool v) { active = v; }
	void setCorner(bool v) { corner = v; }
	void setCenter(bool v) { center = v; }
	void setTotalValue(int v) { totalValue = v;}
	void setPlayer(Owner o) { player = o; }
	void setCard(Card* c, Owner o);
	void deleteCard() const { delete card; } // ???
	void setAdjacents(std::array<Cell*, 4>& a) { adjacents = a; }
	void blockEffects(Cell* c);

	Cell& operator=(const Cell& o)
	{
		// delete current list in data;
		// deep copy o.data to data here;
		return *this;
	}
};
