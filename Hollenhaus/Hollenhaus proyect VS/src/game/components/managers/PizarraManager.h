#pragma once
#include "../ComponentUpdate.h"
#include "../../ecs.h"
#include <list>

class Data;

class PizarraManager : public ComponentUpdate
{
private:
	// Mazo en la pizarra
	std::list<int> mazePrev; // id de las cartas en pizarra
	std::list<Vector2D> mazePos; // posiciones de las cartas en pizarra

	// Auxiliar para el guardado del mazo
	std::list<int> mazeaux; // aux de id de las cartas en pizarra
	std::list<Vector2D> mazePosaux; // aux de posiciones de las cartas en pizarra

	// lista de entidades cartas en la pizarra
	std::list<Transform*> cards;

	// Cantidad de cartas en pizarra
	int cantCards;

public:
	// ---- Constructora/Destructora ----
	PizarraManager();
	~PizarraManager();

	// ---- Metodos heredados ----
	void update() override;
	void initComponent() override;

	// ---- PARA FUERA DE LA PIZARRA ----
	// Guarda el mazo en el data
	void saveMaze();

	// Devuelve true si la carta (id) esta en la pizarra
	bool isOnPizarra(int id);

	// Devuelve true si la pizarra esta llena
	bool isPizarraLlena();

	// ---- PIZARRA ----
	// Aniade carta a la pizarra
	void addCard(int id, Transform* card);

	// Quita carta de la pizarra
	void removeCard(int id);

	// Getter cantidad de cartas en la pizarra
	int getCantCartds() { return cantCards; }
};