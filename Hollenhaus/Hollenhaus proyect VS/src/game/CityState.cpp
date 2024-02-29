#include "CityState.h"
CityState::CityState()
{
	std::cout << "\nLoading City";
}
void CityState::update()
{
	GameState::update();
}
void CityState::render() const
{
	GameState::render();
}
void CityState::refresh()
{
	GameState::refresh();
}

void CityState::onEnter() const
{
	std::cout << "\nentering CityState\n";
	
	//-----Ciudad provisional de fondo:
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("ciudad");
	fondo->getComponent<Transform>()->getGlobalScale().set(1.2f, 0.6f);
	fondo->getComponent<Transform>()->getGlobalPos().set(0, 0);

	//------NPCs que demomento son Caitlyns: (da error cuando pulsas sobre ellas porque la transcion creo que no esta hecha todavia).
	ecs::entity_t npc1 = Instantiate();
	npc1->addComponent<Transform>();
	npc1->addComponent<SpriteRenderer>("npc");
	npc1->addComponent<BoxCollider>();
	//npc1->getComponent<Transform>()->getGlobalScale().set(0.3f, 0.3f);
	npc1->getComponent<Transform>()->getGlobalPos().set(0, 400);
	npc1->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	//npc1->getComponent<BoxCollider>()->setSize(Vector2D(100,100));
	npc1->addComponent<NPC>(5);

	ecs::entity_t npc2 = Instantiate();
	npc2->addComponent<Transform>();
	npc2->addComponent<SpriteRenderer>("npc");
	npc2->addComponent<BoxCollider>();
	//npc2->getComponent<Transform>()->getGlobalScale().set(0.3f, 0.3f);
	npc2->getComponent<Transform>()->getGlobalPos().set(500, 400);
	npc2->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc2->addComponent<NPC>(5);


}

void CityState::onExit() const
{
	std::cout << "\nexit CityState\n";
	GameStateMachine::instance()->getMngr()->Free();
	//ih().clearFunction(InputHandler::MOUSE_LEFT_CLICK_DOWN, [this] {OnLeftClickDown(_scene); });
	//Free del input

}
