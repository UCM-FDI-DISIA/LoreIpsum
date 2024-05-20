#include <../pchs/pch.h>
#include "MatchOverState.h"
#include "ShopState.h"
#include "../components/managers/Manager.h"
#include "../components/basics/TextComponent.h"
#include "../components/basics/SpriteRenderer.h"
#include "../Data.h"
#include "../components/NPC.h"
#include "./game/components/Button.h"
#include "./game/components/Clickable.h"
#include "../components/ClickableText.h"
// Factorias:
#include "../factories/Factory.h"
#include "../factories/FakeCardFactory_v0.h"
MatchOverState::MatchOverState()
{
	TuVieja("Loading MatchOverState");
}
/*MatchOverState::MatchOverState(int w) : winner(w) // Para probar.
{
	TuVieja("Loading MatchOverState");
}*/

void MatchOverState::update()
{
	GameState::update();
}

void MatchOverState::render() const
{
	GameState::render();
}

void MatchOverState::refresh()
{
	GameState::refresh();
}

void MatchOverState::onEnter()
{

	//------FakeCards:
	factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));

	auto continuar = Instantiate(Vector2D(sdlutils().width() - 400, sdlutils().height() - 150));
	continuar->addComponent<TextComponent>("CONTINUAR", "space_grotesk_bold_32", Colors::PEARL_HOLLENHAUS, 200, Text::BoxPivotPoint::CenterCenter, Text::TextAlignment::Center);
	continuar->addComponent<BoxCollider>();
	continuar->getComponent<BoxCollider>()->setSize(Vector2D(220, 40));
	continuar->getComponent<BoxCollider>()->setPosOffset(Vector2D(-100, -20));
	if (j2_ == "8")
	{
		continuar->addComponent<NPC>(GameStates::CINEMATICOUTRO, 0); // Esto es graciosisimo
	}
	else
	{
		continuar->addComponent<NPC>(GameStates::CITY, 0); // Esto es graciosisimo
	}
	continuar->addComponent<ClickableText>(Colors::PEARL_HOLLENHAUS, Colors::PEARL_CLICK, Colors::ROJO_HOLLENHAUS);

	setWindow(data->getWinner());
}

void MatchOverState::onExit()
{
	saveData();
	GameStateMachine::instance()->getMngr()->Free();
}

void MatchOverState::setWindow(int lastWinner)
{
	_text = "batalla";
	int id;

	// Cual es el ultimo ganador de la partida?
	switch (lastWinner)
	{
	case 1: // Empate:
		data->AddMoney(TIE_MONEY_GAIN);
		_money = std::to_string(TIE_MONEY_GAIN);
		_souls = "0";
		break;
	case 2: // Jugador1:
		j2_ = std::to_string(GameStateMachine::instance()->getCurrentState()->getLastDefeatedNPC());
		id = sdlutils().npcs().at(j2_).cardToDrop();

		if (j2_ == "6" || j2_ == "7" || j2_ == "8") // Ids de la tarotista.
		{
			_text = "caso";
			tarotista = true;
			data->AddMoney(TAROT_MONEY_GAIN);
			_money = std::to_string(TAROT_MONEY_GAIN);
			_souls = "1";
			data->AddSouls(SOULS_GAIN); // Gana almas si gana a la tarotista.
		}
		else // NPC normal.
		{
			_text = "batalla";
			tarotista = false;
			data->AddMoney(NPC_MONEY_GAIN);
			_money = std::to_string(NPC_MONEY_GAIN);
			_souls = "0";
		}

		if (id != -1)
		{
			auto card = createCard(id, Vector2D(520, 240));
		}
		break;
	case 3: // Caso si gana el NPC o tatotista:
		_money = "0";
		_souls = "0";
		break;
	default: // Por defecto:
		_money = "0";
		_souls = "0";
		break;
	}


	//------Carta del fondo.
	ecs::entity_t noCard = Instantiate(Vector2D());
	noCard->getComponent<Transform>()->setGlobalPos(520, 240);
	noCard->getComponent<Transform>()->setGlobalScale(0.5, 0.5);
	noCard->addComponent<SpriteRenderer>("no_card");
	noCard->setLayer(0);
	//------Texto fin batalla/caso:
	ecs::entity_t matchOverText = Instantiate(Vector2D());
	matchOverText->getComponent<Transform>()->setGlobalPos(250, 200);
	matchOverText->addComponent<TextComponent>("Resultado fin de " + _text, Fonts::GROTESK_24, Colors::ROJO_HOLLENHAUS, 500, Text::CenterCenter, Text::Left);
	matchOverText->setLayer(1);
	//------Texto fin batalla/caso:
	ecs::entity_t cardWonText = Instantiate(Vector2D());
	cardWonText->getComponent<Transform>()->setGlobalPos(550, 200);
	cardWonText->addComponent<TextComponent>("Carta ganada", Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::CenterCenter, Text::Left);
	cardWonText->setLayer(1);
	//------Texto dinero ganado:
	ecs::entity_t moneyWon = Instantiate(Vector2D());
	moneyWon->getComponent<Transform>()->setGlobalPos(150, 250);
	moneyWon->addComponent<TextComponent>("Dinero ganado\n+" + _money + " DM", Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::LeftCenter, Text::Left);
	moneyWon->setLayer(1);
	//------Texto almas ganado:
	ecs::entity_t soulsWon = Instantiate(Vector2D());
	soulsWon->getComponent<Transform>()->setGlobalPos(150, 320);
	soulsWon->addComponent<TextComponent>("Almas ganadas\n+" + _souls, Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::LeftCenter, Text::Left);
	soulsWon->setLayer(1);



	// ---- Resetea el ganador a nulo al salir del estado ----
	data->setWinner(0);
}

void MatchOverState::setJ2(std::string rival)
{
	j2_ = rival;
}

ecs::entity_t MatchOverState::createCard(int id, Vector2D pos)
{
	// Hace LA carta
	auto card = sdlutils().cards().at(std::to_string(id));
	ecs::entity_t ent = factory->createFakeCard(id, pos, card.cost(), card.value(), card.sprite(), card.unblockable(), card.effects());
	return ent;
}