#include "SamuState.h"

#include "Entity.h"
#include "GameStateMachine.h"
#include "Manager.h"

#include "../SpriteRenderer.h"
#include "../Transform.h"

SamuState::SamuState() : GameState() {

	auto mngr = GameStateMachine::instance()->getMngr();

	card = mngr->addEntity();
	
	mngr->addComponent<Transform>(card);
	mngr->addComponent<SpriteRenderer>(card, "./resources/images/card.png");
	mngr->getComponent<Transform>(card)->getRealativeScale().set(1.0, 1.0);

	std::cout << mngr->getComponent<Transform>(card)->getRealativeScale() << std::endl;
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

}

void SamuState::render() const
{
	GameState::render();
}
