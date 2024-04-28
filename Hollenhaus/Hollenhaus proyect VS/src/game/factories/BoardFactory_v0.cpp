#include <../pchs/pch.h>

#include "BoardFactory_v0.h"
#include "../components/managers/Manager.h"
#include "../components/basics/Transform.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/ShineComponent.h"
#include "../components/basics/BoxCollider.h"
#include "../components/Drag.h"
#include "../components/managers/BoardManager.h"
#include "../components/DropDetector.h"
#include "../../utils/Vector2D.h"
#include "../../sdlutils/SDLUtils.h"
#include "../ecs.h"
#include "../components/Cell.h"

ecs::entity_t BoardFactory_v0::createBoard()
{
	// odio estos putisimos numeros
	int initialX = 260;//284
	int initialY = 90-9;//135
	int offSetX = 67;//62
	int offSetY = 96;//84



	float scale = 0.53;//0.45

	std::vector<std::vector<ecs::entity_t>> _board;

	ecs::entity_t cellImage;
	// Seteamos el board al tamanio deseado
	_board.resize(size);
	for (int i = 0; i < size; i++)
	{
		_board[i].resize(size);
	}

	/// Inicializacion de cada celda como entidad vacia
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			//PARTE VISUAL
			_board[i][j] = Instantiate(Vector2D(initialX + i * offSetX, initialY + j * offSetY), ecs::grp::DROPS);

			_board[i][j]->addComponent<DropDetector>()->getCardPos().set(
				Vector2D(initialX + i * offSetX, initialY + j * offSetY));
			_board[i][j]->getComponent<DropDetector>()->getBoardPos().set(
				Vector2D(i, j));
			_board[i][j] ->addComponent<SpriteRenderer>("cell");
			_board[i][j]->addComponent<ShineComponent>();
			_board[i][j]->getComponent<ShineComponent>()
				->addEnt(_board[i][j]->getComponent<SpriteRenderer>(), "shine_cell");

			//npc->getComponent<ShineComponent>()->addEnt(npc->getComponent<SpriteRenderer>(), "BrilliNPC");
			_board[i][j]->getComponent<Transform>()->setGlobalScale(Vector2D(scale, scale));
			_board[i][j]->addComponent<BoxCollider>();
			_board[i][j]->getComponent<BoxCollider>()->setAnchoredToSprite(true);
			/*_board[i][j]->getComponent<BoxCollider>()->setSize(
				Vector2D(sdlutils().images().at("card").width() * scale,
					(sdlutils().images().at("card").height()) * scale));*/
			_board[i][j]->addComponent<Cell>();
			_board[i][j]->setLayer(2);
			/*
			cellImage = Instantiate(Vector2D(initialX + i * offSetX, initialY + j * offSetY));
			cellImage->setLayer(1);*/

		}
	}

	//crear una entidad
	ecs::Entity* boardEntity = Instantiate(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2));

	//añadimos a la entidad el componente boardManager y le seteamos el board que hemos creado
	boardEntity->addComponent<BoardManager>()->setBoard(_board);


	return boardEntity;
}
