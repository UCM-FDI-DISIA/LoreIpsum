#include "pch.h"
#include "DrawerManager.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"
#include "../../components/Card.h"
#include "../../components/CardDestroyer.h"
#include "Manager.h"

DrawerManager::DrawerManager() : cajonesAbiertos(0),
drawer(GameStateMachine::instance()->getCurrentState()->getDrawer()) {}

DrawerManager::~DrawerManager() {}

#pragma region REFRESHERS
void DrawerManager::refreshExistencia()
{
	// Esto deberia ir en el refresh pero no funciona asique va aqui

	// recorre las cartas mostradas
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		// si existe esa carta
		if (cardsAux[i] != nullptr)
		{
			// !!!!!!!!!!!!! aqui se deberian de eliminar las cartas
			// pero como no funciona pq da error en noseque
			// del child, se va a quedar asi :) 

			// guarda la entidad
			ecs::entity_t ent = cardsAux[i];

			// la mata
			ent_->getComponent<CardDestroyer>()->destroyCard();

			// la pone a nullptr
			cardsAux[i] = nullptr;
		}
	}

	// recorre las cartas mostradas
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		// si la carta esta desbloqueada
		if (drawer[(CANT_CARTAS_MOSTRADAS_CAJON * cajonesAbiertos) + i] != -1)
		{
			// la crea
			ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
			(drawer[(CANT_CARTAS_MOSTRADAS_CAJON * cajonesAbiertos) + i], Vector2D(25 * i, 100));

			// si existe
			if (ent != nullptr) {

				// la guarda en el aux
				cardsAux[i] = ent;

				// refresca la pos (pone la carta en la pos que le toque)
				refreshPos(i, cardsAux[i]);
			}
		}
	}
}

void DrawerManager::refreshPos(int i, ecs::entity_t ent)
{
	ent->getComponent<Transform>()->setGlobalPos(refreshPositions[i]);
}
#pragma endregion

void DrawerManager::update() {}

void DrawerManager::initComponent()
{
	// recorre todas las cartas de un cajon
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		// las pone a nullptr
		cardsAux[i] = nullptr;
	}

	// las rellena
	refreshExistencia();
}

void DrawerManager::saveDrawer()
{
	// settea drawer del data
	GameStateMachine::instance()->getCurrentState()->setDrawer(drawer);
}

bool DrawerManager::isOnDrawer(int id)
{
	// devuelve true si el id de la carta concide con el contenido en esa pos
	return drawer[id] == id;
}

#pragma region METE Y SACA CARTA

// refresca la pos de la carta en el cajon
void DrawerManager::addCard(int id, ecs::entity_t ent)
{
	drawer[id] = id;
	cardsAux[id % CANT_CARTAS_MOSTRADAS_CAJON] = ent;
	refreshPos(id % CANT_CARTAS_MOSTRADAS_CAJON, cardsAux[id % CANT_CARTAS_MOSTRADAS_CAJON]);

	// DEBUG
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::removeCard(int id)
{
	// en la pos segun id de la carta del drawer ahora se guarda -1 (hueco vacio)
	drawer[id] = -1;

	// pone en su pos de las cartas que se muestran en ese instante a null
	cardsAux[id % CANT_CARTAS_MOSTRADAS_CAJON] = nullptr;

	// DEBUG
	std::cout << drawer[id] << std::endl;
}
#pragma endregion

#pragma region BOTONES
void DrawerManager::drawerPalante()
{
	TuVieja("drawerPalante");

	// si no has llegado al ultimo cajon
	if (cajonesAbiertos < CARDS_IN_GAME / CANT_CARTAS_MOSTRADAS_CAJON)
	{
		// aumentas el indice de cajones abiertos
		cajonesAbiertos++;
	}

	// se actualizan las cartas mostradas
	refreshExistencia();
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");

	// si no has llegado al primer cajon
	if (cajonesAbiertos > 0)
	{
		// disminuyes el indice de cajones abiertos
		cajonesAbiertos--;
	}

	// se actualizan las cartas mostradas
	refreshExistencia();
}
#pragma endregion