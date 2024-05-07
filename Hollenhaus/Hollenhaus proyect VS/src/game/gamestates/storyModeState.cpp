#include <../pchs/pch.h>

#include "storyModeState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/TextComponent.h"
#include "../components/Button.h"
#include "../components/NPC.h"
#include "../components/basics/Transform.h"
#include "game/components/Clickable.h"
#include "game/components/ClickableText.h"

constexpr SDL_Color PEARL_HOLLENHAUS = { 226, 223, 210, 255 };
constexpr SDL_Color PEARL_CLICK = { 250, 248, 240, 255 };
constexpr SDL_Color ROJO_HOLLENHAUS = { 148, 47, 55, 255 };


StoryModeState::StoryModeState()
{
	
}

StoryModeState::~StoryModeState()
{
}

void StoryModeState::refresh()
{
	GameState::refresh();
}

void StoryModeState::update()
{
	GameState::update();
}

void StoryModeState::render() const
{
	GameState::render();
}

void StoryModeState::onEnter()
{
	ecs::entity_t fondo = Instantiate();
	fondo->addComponent<Transform>();
	fondo->addComponent<SpriteRenderer>("optfondo");
	fondo->getComponent<Transform>()->setGlobalScale(100, 100);
	//fondo->getComponent<Transform>()->getRelativeScale().set(5.0f, 5.0f);
	fondo->setLayer(0);

	auto firstFrame = "boton_flecha";
	returnButton = Instantiate(Vector2D(50, 50));
	returnButton->addComponent<Transform>();
	returnButton->addComponent<BoxCollider>();
	returnButton->addComponent<SpriteRenderer>(firstFrame);
	returnButton->addComponent<Clickable>(firstFrame, true);
	/// Si queremos fade in / fade out en la clase Button en vez de NPC hay que gestionar
	///	las llamadas a la logica de los fades en esa clase, asi que de momento voy a
	///	hacerlo con npc y punto pero aviso porsiaca
	//returnButton->addComponent<Button>();
	//returnButton->getComponent<Button>()->connectToButton([this]
	//{
	//	//GameStateMachine::instance()->setState(0); // usar enums en vez de numeros a palo seco
	//	GameStateMachine::instance()->setState(GameStates::MAINMENU); // usar enums en vez de numeros a palo seco
	//});
	returnButton->addComponent<NPC>(GameStates::MAINMENU, NPC::Type::BUTTON, "", true, true);


	newGameButton = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 300));
	newGameButton->addComponent<TextComponent>("NUEVA PARTIDA", "8bit_size_32", PEARL_HOLLENHAUS, 300, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	newGameButton->addComponent<BoxCollider>();
	newGameButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	newGameButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	newGameButton->addComponent<NPC>(15, 0);
	newGameButton->addComponent<ClickableText>(PEARL_HOLLENHAUS, PEARL_CLICK, ROJO_HOLLENHAUS);

	continueButton = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 250));
	continueButton->addComponent<TextComponent>("CONTINUAR", "8bit_size_32", PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	continueButton->addComponent<BoxCollider>();
	continueButton->getComponent<BoxCollider>()->setSize(Vector2D(300, 40));
	continueButton->getComponent<BoxCollider>()->setPosOffset(Vector2D(-150, -20));
	continueButton->addComponent<NPC>(15, 0);
	continueButton->addComponent<ClickableText>(PEARL_HOLLENHAUS, PEARL_CLICK, ROJO_HOLLENHAUS);
}

void StoryModeState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();

}
