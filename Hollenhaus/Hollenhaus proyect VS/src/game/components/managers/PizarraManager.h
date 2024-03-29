#pragma once
#include "../ComponentUpdate.h"
#include "../../ecs.h"
#include <list>

class Data;

class PizarraManager : public ComponentUpdate
{
private:
	// Mazo en la pizarra
	std::list<int> mazePrev;
	std::list<Vector2D> mazePos;
	// Auxiliar para el guardado del mazo
	std::list<int> mazeaux;
	std::list<Vector2D> mazePosaux;

	// lista de entidades cartas en la pizarra
	std::list<Transform*> cards;

	// Cantidad de cartas en el mazo
	int cantCards;

public:
	// ---- Constructora/Destructora ----
	PizarraManager();
	~PizarraManager();

	// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
	void update() override;
	void initComponent() override;

	void refreshPos();

	// ---- PARA FUERA PIZARRA ----
	// Guarda el mazo en el data.
	void saveMaze();

	// Devuelve true si la carta (id) esta en la pizarra.
	bool isOnPizarra(int id);

	// Devuelve true si la pizarra esta llena
	bool isPizarraLlena();

	// ---- PIZARRA ----
	// Aniade carta a la pizarra
	void addCard(int id, Transform* card);

	// Quita carta de la pizarra
	void removeCard(int id);
};