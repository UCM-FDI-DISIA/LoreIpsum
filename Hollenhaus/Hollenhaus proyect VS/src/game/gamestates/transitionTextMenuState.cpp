#include <../pchs/pch.h>
#include "transitionTextMenuState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/NPC.h"
#include "../components/basics/SpriteRenderer.h"
#include "../components/basics/Transform.h"
#include "game/components/ClickableText.h"


constexpr SDL_Color PEARL_HOLLENHAUS = { 226, 223, 210, 255 };

TransitionTextMenuState::TransitionTextMenuState() : rand_(sdlutils().rand())
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

	auto font = "space_grotesk_bold_40";
	auto posXTexts = 300;
	auto posYTexts = 90;
	auto sepYTexts = 50;
	auto posXNums = 420;
	auto textSize = 200;
	auto numSize = 300;
	casoText = Instantiate(Vector2D(posXTexts, posYTexts));
	casoText->addComponent<TextComponent>("CASO: ", font, PEARL_HOLLENHAUS, textSize, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	casoText->setLayer(1);

	caso = GameStateMachine::instance()->getCurrentState()->getCurrentCase();

	casoNum = Instantiate(Vector2D(posXNums, posYTexts));
	casoNum->addComponent<TextComponent>(std::to_string(caso), font, PEARL_HOLLENHAUS, numSize, Text::BoxPivotPoint::LeftCenter, Text::TextAlignment::Left);
	casoNum->setLayer(1);

	dineroText = Instantiate(Vector2D(posXTexts, posYTexts + sepYTexts));
	dineroText->addComponent<TextComponent>("DINERO: ", font, PEARL_HOLLENHAUS, textSize, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	dineroText->setLayer(1);

	money = GameStateMachine::instance()->getCurrentState()->getMoney();

	dineroNum = Instantiate(Vector2D(posXNums, posYTexts + sepYTexts));
	dineroNum->addComponent<TextComponent>(std::to_string(money), font, PEARL_HOLLENHAUS, numSize, Text::BoxPivotPoint::LeftCenter, Text::TextAlignment::Left);
	dineroNum->setLayer(1);
	
	almasText = Instantiate(Vector2D(posXTexts, posYTexts + sepYTexts * 2));
	almasText->addComponent<TextComponent>("ALMAS: ", font, PEARL_HOLLENHAUS, textSize, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	almasText->setLayer(1);

	almas = GameStateMachine::instance()->getCurrentState()->getSouls();

	almasNum = Instantiate(Vector2D(posXNums, posYTexts + sepYTexts * 2));
	almasNum->addComponent<TextComponent>(std::to_string(almas), font, PEARL_HOLLENHAUS, numSize, Text::BoxPivotPoint::LeftCenter, Text::TextAlignment::Left);
	almasNum->setLayer(1);

	chascarrillo = Instantiate(Vector2D(400, 350));

	int i = rand_.nextInt(0, 10);

	switch (i) 
	{
		case 0:
			Ctext = "Para un economista la vida real es un caso especial";
			break;
		case 1:
			Ctext = "Le pedí a un economista su número de teléfono y me dio su estimación";
			break;
		case 2:
			Ctext = "¿Cuándo puedes decir que un economista está mintiendo? Cuando se mueven sus labios";
			break;
		case 3:
			Ctext = "¿Sabes a dónde van las pulgas cuando mueren? Al pulgatorio";
			break;
		case 4:
			Ctext = "¿Por qué los fantasmas nunca hacen la colada? Porque corren el peligro de meter en la lavadora a sus parientes";
			break;
		case 5:
			Ctext = "Van dos fantasmas y se cae el del médium";
			break;
		case 6:
			Ctext = "¿Has probado a poner el nombre completo del fantasma protagonista en el traductor de alemán?";
			break;
		case 7:
			Ctext = "¿Sabías que Paul murió sacrificado por una secta?";
			break;
		case 8:
			Ctext = "¿Sabías que Paul tuvo una aparición en La Nave del Misterio?";
			break;
		case 9:
			Ctext = "¿Sabías que las únicas humanas de Höllenhaus que pueden ver a Paul son la tendera y la médium?";
			break;

	}

	chascarrillo->addComponent<TextComponent>(Ctext, font, PEARL_HOLLENHAUS, 600, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	chascarrillo->setLayer(1);


	continuar = Instantiate(Vector2D(sdlutils().width() - 420, sdlutils().height() - 100));
	continuar->addComponent<TextComponent>(
		"CONTINUAR", font, PEARL_HOLLENHAUS, 
		220, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Right);
	continuar->addComponent<BoxCollider>();
	continuar->getComponent<BoxCollider>()->setSize(Vector2D(220, 40));
	continuar->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	continuar->addComponent<NPC>(1, 0); // Esto es graciosisimo
	continuar->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);
}

void TransitionTextMenuState::onExit()
{
	GameStateMachine::instance()->getMngr()->Free();

}
