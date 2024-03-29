#pragma once
#include "../ComponentUpdate.h"
#include "../../Data.h"
#include "../../ecs.h"
#include "../../../utils/Vector2D.h"
#include <array>

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
	// crea las cartas del cajon en un rango
	void refreshExistencia();
	// Refresca las posiciones de las cartas en el cajon
	void refreshPos(int i, ecs::entity_t ent);

public:
	// ---- Constructora/Destructora ----
	DrawerManager();
	~DrawerManager();

	// ---- Metodos heredados (no es TAAAAAAAAN importante) ----
	void update() override;
	void initComponent() override;

	// Guarda el drawer en el data
	void saveDrawer();

	// Comprueba si un id esta en el drawer
	bool isOnDrawer(int id);

	// ---- Manageos de carta ----
	// Aniade carta
	void addCard(int id);

	// Quita carta
	void removeCard(int id);

	// ---- Manageos de botones ----
	// muestra las siguientes n cartas
	void drawerPalante();

	// muestra las anteriores n cartas
	void drawerPatras();

};

