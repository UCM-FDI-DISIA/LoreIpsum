#include <../pchs/pch.h>

#include "ClickDecision.h"

#include "../components/NextText.h"
#include "../components/DialogueDestroyer.h"
#include "../components/DialogueEventCollection.h"
#include "../components/DecisionComponent.h"
#include "../components/ShopComponent.h"
#include "../CaseManager.h"
#include "../factories/Factory.h"
#include "../factories/NPCFactory_V0.h"
#include "../components/NPC.h"

ClickDecision::ClickDecision(int decision, ecs::entity_t parent, int scene)
{
	decision_ = decision;
	parent_ = parent;
	scene_ = scene;
	click_ = false;

	ih().insertFunction(ih().MOUSE_LEFT_CLICK_DOWN, [this] { OnLeftClickDown(); });
	ih().insertFunction(ih().MOUSE_LEFT_CLICK_UP, [this] { OnLeftClickUp(); });
}

ClickDecision::~ClickDecision()
{
}

void ClickDecision::initComponent()
{
	scene_ = 0;
	myNpc_ = parent_->getComponent<Transform>()->getParent()->getEntity()->getComponent<Transform>()->getParent()->getEntity()->getComponent<NPC>();
}

void ClickDecision::update()
{
}

void ClickDecision::OnLeftClickDown()
{
	if (mouseRaycast() == ent_)
	{
		click_ = true;
		TakeDecision();
	}
}

void ClickDecision::OnLeftClickUp()
{
	click_ = false;
}

void ClickDecision::TakeDecision()
{
	switch (decision_)
	{
	case 0: // Para decir no.

		TuVieja("No");
		cancelPurchase();
		parent_->getComponent<NextText>()->setDead(true);
		parent_->getComponent<DialogueDestroyer>()->destroyDialogue();
		break;

	case 1: // Para cambiar de escena.

		TuVieja("Cambio de escena");
		parent_->getComponent<DialogueEventCollection>()->ChangeScene(scene_);
		//abria que hacer actual node ++?¿?¿


		break;
	case 2: // Para confirmar compra.

		purchaseCard();
		parent_->getComponent<NextText>()->setDead(true);
		parent_->getComponent<DialogueDestroyer>()->destroyDialogue();

		break;
	case 3: // Caso aceptado
		TuVieja("Buenos dias caso 3");
		caseAccepted();
		break;
	case 4: // CASO DEAFULT PARA NEGAR CUALQUIER COSA
		parent_->getComponent<NextText>()->setDead(true);
		parent_->getComponent<DialogueDestroyer>()->destroyDialogue();
		break;
	case 5:
		parent_->getComponent<DialogueEventCollection>()->ChangeScene(GameStates::LUIS);
		GameStateMachine::instance()->getCurrentState()->setJ2(std::to_string(myNpc_->getID()));
		break;
	default:
		TuVieja("Esta decision no existe. Añadir en ClickDecision.cpp");
		break;
	}
	
}

void ClickDecision::setScene(int s)
{
	scene_ = s;
}

void ClickDecision::purchaseCard()
{
	TuVieja("Carta comprada.");
	ecs::entity_t ent = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::DECISION_MANAGER);
	if (ent->hasComponent<DecisionComponent>())
	{
		ent->getComponent<DecisionComponent>()->setBuying(1);
	}
}

void ClickDecision::cancelPurchase()
{
	TuVieja("Cancelar compra.");
	ecs::entity_t ent = GameStateMachine::instance()->getMngr()->getHandler(ecs::hdlr::DECISION_MANAGER);
	if (ent->hasComponent<DecisionComponent>())
	{
		ent->getComponent<DecisionComponent>()->setBuying(0);
		ent->getComponent<DecisionComponent>()->resetCardToPurchase();
	}
}

void ClickDecision::caseAccepted()
{
	if (click_) {
		TuVieja("CASO ACEPTADO");
		CaseManager* caseMngr = GameStateMachine::instance()->caseMngr();
		caseMngr->setAccepted(true);

		NPC* npc = caseMngr->caseNPC()->getComponent<NPC>();
		npc->nextConvo();
	}
}
