#include <../pchs/pch.h>

#include "transitionTextMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"

constexpr SDL_Color PEARL_HOLLENHAUS = { 226, 223, 210, 255 };

TransitionTextMenuState::TransitionTextMenuState()
{
}

TransitionTextMenuState::~TransitionTextMenuState()
{
}

void TransitionTextMenuState::refresh()
{
	GameState::refresh();

}

void TransitionTextMenuState::update()
{
	GameState::update();

}

void TransitionTextMenuState::render() const
{
	GameState::render();

}

void TransitionTextMenuState::onEnter()
{
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(100, 100);
	//fondo->getComponent<Transform>()->getRelativeScale().set(5.0f, 5.0f);
	fondo->setLayer(0);

	casoText = Instantiate(Vector2D(370, 100));
	casoText->addComponent<TextComponent>("CASO ", "8bit_size_40", PEARL_HOLLENHAUS, 130, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	casoText->setLayer(1);

	caso = GameStateMachine::instance()->getCurrentState()->getCurrentCase();

	casoNum = Instantiate(Vector2D(440, 95));
	casoNum->addComponent<TextComponent>(std::to_string(caso), "8bit_size_40", PEARL_HOLLENHAUS, 90, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	casoNum->setLayer(1);

	dineroText = Instantiate(Vector2D(340, 170));
	dineroText->addComponent<TextComponent>("DINERO: ", "8bit_size_40", PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	dineroText->setLayer(1);

	money = GameStateMachine::instance()->getCurrentState()->getMoney();

	dineroNum = Instantiate(Vector2D(490, 170));
	dineroNum->addComponent<TextComponent>(std::to_string(money), "8bit_size_40", PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Left);
	dineroNum->setLayer(1);

	continuar = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 100));
	continuar->addComponent<TextComponent>("CONTINUAR", "8bit_size_32", PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	continuar->addComponent<BoxCollider>();
	continuar->getComponent<BoxCollider>()->setSize(Vector2D(200, 40));
	continuar->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	continuar->addComponent<NPC>(1, 0); // Esto es graciosisimo
}

void TransitionTextMenuState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();

}
