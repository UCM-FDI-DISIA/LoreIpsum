#include "BoardFactory_v0.h"

#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "BoardManager.h"
#include "DropDetector.h"
#include "CellManager.h"

#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs.h"




ecs::entity_t BoardFactory_v0::createBoard()
{
	// odio estos putisimos numeros
	int initialX = 284;
	int initialY = 135;
	int offSetX = 62;
	int offSetY = 84;

	float scale = 0.45;

	std::vector<std::vector<ecs::entity_t>> _board;

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
			auto cellCmp = _board[i][j]->addComponent<CellManager>();
			_board[i][j]->addComponent<BoxCollider>();
			_board[i][j]->addComponent<DropDetector>()->getCardPos().set(
				Vector2D(initialX + i * offSetX, initialY + j * offSetY));
			_board[i][j]->addComponent<Cell>();

			_board[i][j]->getComponent<DropDetector>()->getBoardPos().set(Vector2D(i, j));
			_board[i][j]->getComponent<BoxCollider>()->setSize(
				Vector2D(sdlutils().images().at("card").width() * scale,
					(sdlutils().images().at("card").height()) * scale));

			cellCmp->setPosOnBoard(i, j);
		}
	}

	//crear una entidad
	ecs::Entity* boardEntity = Instantiate(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2));


	//añadimos a la entidad el componente boardManager y le seteamos el board que hemos creado
	boardEntity->addComponent<BoardManager>()->setBoard(_board);



	return boardEntity;
}
