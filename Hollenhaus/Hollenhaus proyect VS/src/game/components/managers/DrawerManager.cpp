#include "pch.h"
#include "DrawerManager.h"
#include "../../GameStateMachine.h"
#include "../../gamestates/GameState.h"
#include "Manager.h"


DrawerManager::DrawerManager() : cajonesAbiertos(0),
drawer(GameStateMachine::instance()->getCurrentState()->getDrawer())
{
}

DrawerManager::~DrawerManager()
{
}

void DrawerManager::refreshExistencia()
{
	// Esto deberia ir en el refresh pero no funciona asique va aqui
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		if (cardsAux[i] != nullptr)
		{
			//aqui se deberian de eliminar las cartas pero como no funciona pq da error en noseque
			// del child, se va a quedar asi :)
			ecs::entity_t ent = cardsAux[i];
			ent->getComponent<Transform>()->killChilds();
			ent->setAlive(false);
			cardsAux[i] = nullptr;
			//Vector2D pos0(0, 0);
			//cardsAux[i]->getComponent<Transform>()->setGlobalPos(pos0);
		}
	}

	
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		if (drawer[(CANT_CARTAS_MOSTRADAS_CAJON * cajonesAbiertos) + i] != -1)
		{
			ecs::entity_t ent = GameStateMachine::instance()->getCurrentState()->createCard
			(drawer[(CANT_CARTAS_MOSTRADAS_CAJON * cajonesAbiertos) + i], Vector2D(25 * i, 100));
			if (ent != nullptr) {
				cardsAux[i] = ent;

				refreshPos(i, cardsAux[i]);
			}

		}
	}
}

void DrawerManager::refreshPos(int i, ecs::entity_t ent)
{
	ent->getComponent<Transform>()->setGlobalPos(refreshPositions[i]);
}

void DrawerManager::update()
{
}

void DrawerManager::initComponent()
{
	for (int i = 0; i < CANT_CARTAS_MOSTRADAS_CAJON; i++)
	{
		cardsAux[i] = nullptr;
	}
	refreshExistencia();

}

void DrawerManager::saveDrawer()
{
	GameStateMachine::instance()->getCurrentState()->setDrawer(drawer);
}

bool DrawerManager::isOnDrawer(int id)
{
	return drawer[id] == id;
}

void DrawerManager::addCard(int id)
{
	drawer[id] = id;
	refreshPos(id % CANT_CARTAS_MOSTRADAS_CAJON, cardsAux[id % CANT_CARTAS_MOSTRADAS_CAJON]);
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::removeCard(int id)
{
	drawer[id] = -1;
	cardsAux[id % CANT_CARTAS_MOSTRADAS_CAJON] = nullptr;
	std::cout << drawer[id] << std::endl;
}

void DrawerManager::drawerPalante()
{
	TuVieja("drawerPalante");
	if (cajonesAbiertos < CARDS_IN_GAME / CANT_CARTAS_MOSTRADAS_CAJON)
	{
		cajonesAbiertos++;
	}
	refreshExistencia();
}

void DrawerManager::drawerPatras()
{
	TuVieja("drawerPatras");
	if (cajonesAbiertos > 0)
	{

		cajonesAbiertos--;
	}
	refreshExistencia();
}
