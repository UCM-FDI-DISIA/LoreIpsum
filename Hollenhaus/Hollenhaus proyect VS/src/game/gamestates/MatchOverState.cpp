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
//#include "../../sdlutils/SDLUtils.h"

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
	std::cout << "\nENTER MATCHOVER.\n";

	//------FakeCards:
	factory = new Factory();
	factory->SetFactories(static_cast<FakeCardFactory*>(new FakeCardFactory_v0()));

	//------Boton para volver:
	ecs::entity_t exit = Instantiate();
	exit->addComponent<Transform>();
	exit->addComponent<SpriteRenderer>("boton_flecha");
	exit->addComponent<BoxCollider>();
	Vector2D exitPos(10, 10);
	exit->getComponent<Transform>()->setGlobalPos(exitPos);
	exit->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	if (j2_ == "8") {
		exit->addComponent<Button>();
		exit->getComponent<Button>()->connectToButton([this]
			{
				GameStateMachine::instance()->setState(GameStates::ENDGAME);
			});
	}
	else
	{
		exit->addComponent<NPC>(1); // Lleva a la ciudad (1).
	}
	exit->setLayer(1);
	exit->addComponent<Clickable>("boton_flecha", true);

	setWindow(data->getWinner());
}

void MatchOverState::onExit()
{
	saveData();
	std::cout << "\nEXIT MATCHOVER.\n";
	GameStateMachine::instance()->getMngr()->Free();
}

void MatchOverState::setWindow(int lastWinner)
{
	//j2_ = "12";
	j2_ = GameStateMachine::instance()->getCurrentState()->getLastDefeatedNPC(); // PAIGRO AQUI descomentar.
	int id = sdlutils().npcs().at(j2_).cardToDrop();

	if (j2_ == "6" || j2_ == "7" || j2_ == "8") // Ids de la tarotista.
	{
		_text = "caso:";
		tarotista = true;
	}
	else // NPC normal.
	{
		_text = "batalla:";
		tarotista = false;
	}


	// Cual es el ultimo ganador de la partida?
	switch (lastWinner)
	{
	case 1: // Empate:
		data->AddMoney(TIE_MONEY_GAIN);
		_money = std::to_string(TIE_MONEY_GAIN);
		_souls = "0";
		break;
	case 2: // Jugador1:
		if (tarotista) // Id de la tarotista.
		{
			data->AddMoney(TAROT_MONEY_GAIN);
			_money = std::to_string(TAROT_MONEY_GAIN);
			_souls = "1";
			data->AddSouls(SOULS_GAIN); // Gana almas si gana a la tarotista.
		}
		else // NPC normal.
		{
			data->AddMoney(NPC_MONEY_GAIN);
			_money = std::to_string(NPC_MONEY_GAIN);
			_souls = "0";
		}

		if (id != -1)
		{
			auto card = createCard(id, Vector2D(570, 230));
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


	//------Texto fin batalla/caso:
	ecs::entity_t matchOverText = Instantiate(Vector2D());
	matchOverText->getComponent<Transform>()->setGlobalPos(400, 100);
	matchOverText->addComponent<TextComponent>("Resultado fin de " + _text, Fonts::GROTESK_40, Colors::PEARL_HOLLENHAUS, 500, Text::CenterCenter, Text::Center);
	matchOverText->setLayer(1);
	//------Texto fin batalla/caso:
	ecs::entity_t cardWonText = Instantiate(Vector2D());
	cardWonText->getComponent<Transform>()->setGlobalPos(600, 200);
	cardWonText->addComponent<TextComponent>("Carta ganada:", Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::CenterCenter, Text::Center);
	cardWonText->setLayer(1);
	//------Texto dinero ganado:
	ecs::entity_t moneyWon = Instantiate(Vector2D());
	moneyWon->getComponent<Transform>()->setGlobalPos(200, 200);
	moneyWon->addComponent<TextComponent>("Dinero ganado:\n" + _money + " DM", Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::CenterCenter, Text::Center);
	moneyWon->setLayer(1);
	//------Texto almas ganado:
	ecs::entity_t soulsWon = Instantiate(Vector2D());
	soulsWon->getComponent<Transform>()->setGlobalPos(200, 300);
	soulsWon->addComponent<TextComponent>("Almas ganadas:\n" + _souls, Fonts::GROTESK_24, Colors::PEARL_HOLLENHAUS, 500, Text::CenterCenter, Text::Center);
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