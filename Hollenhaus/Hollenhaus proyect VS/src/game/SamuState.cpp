#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "ColliderRender.h"
#include "Drag.h"
#include "CardStateManager.h"
#include "DragManager.h"

#include "CardFactory_v0.h"

SamuState::SamuState() : GameState() {


	CardFactory_v0* factory = new CardFactory_v0();

	factory->createBoard();
	factory->createHand();
	//card->setLayer(1);

	ecs::entity_t ent = Instantiate();
	ent->addComponent<DragManager>();
}

SamuState::~SamuState()
{

}

void SamuState::refresh()
{
	GameState::refresh();
}

void SamuState::update()
{
	GameState::update();

	//std::cout << mouseRaycast()<< std::endl;
}

void SamuState::render() const
{
	GameState::render();
}
