#pragma once
#include "../ComponentUpdate.h"
#include "../../Data.h"
#include "../../ecs.h"
#include "../../../utils/Vector2D.h"
#include <array>

// cuantas cartas hay por cajon
const int CANT_CARTAS_MOSTRADAS_CAJON = 6;

class DrawerManager : public ComponentUpdate
{
private:
	// Cartas desbloqueadas
	std::array<int, CARDS_IN_GAME> drawer;

	// posiciones de la carta en el cajon
	std::array<Vector2D, CANT_CARTAS_MOSTRADAS_CAJON> refreshPositions{
		Vector2D(400, 420),
		Vector2D(425, 420),
		Vector2D(450, 420),
		Vector2D(475, 420),
		Vector2D(500, 420),
		Vector2D(525, 420)
	};

	// lleva la cuenta de en que cajon estamos
	int cajonesAbiertos;

	// Array auxiliar para guardar las cartas actuales del cajon
	std::array<ecs::entity_t, CANT_CARTAS_MOSTRADAS_CAJON> cardsAux;

	// ---- Manageos externos ----
	// crea las cartas del cajon en el rango CANT_CARTAS_MOSTRADAS_CAJON
	void refreshExistencia();

	// Refresca las posiciones de las cartas en el cajon
	void refreshPos(int i, ecs::entity_t ent);

public:
	// ---- Constructora/Destructora ----
	DrawerManager();
	~DrawerManager();

	// ---- Metodos heredados ----
	void update() override;
	void initComponent() override;

	// ---- CAJON ----
	// Guarda el drawer en el data
	void saveDrawer();

	// Comprueba si un id esta en el drawer
	bool isOnDrawer(int id);

	// ---- CARTAS ----
	// Aniade carta
	void addCard(int id);

	// Quita carta
	void removeCard(int id);

	// ---- BOTONES ----
	// muestra las siguientes n cartas
	void drawerPalante();

	// muestra las anteriores n cartas
	void drawerPatras();
};