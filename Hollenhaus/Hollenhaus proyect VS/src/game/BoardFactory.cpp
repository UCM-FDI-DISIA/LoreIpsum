#include "BoardFactory.h"

#include "Manager.h"

#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "BoardManager.h"
#include "DropDetector.h"

#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"

BoardFactory::BoardFactory(int w, int h) :
	width(w),
	heigth(h)
{
}

ecs::Entity* BoardFactory::createBoard()
{
	ecs::Entity* boardEntity = Instantiate(Vector2D(sdlutils().width() / 2, sdlutils().height() / 2));

	boardEntity->addComponent<BoardManager>();

	return boardEntity;
}
