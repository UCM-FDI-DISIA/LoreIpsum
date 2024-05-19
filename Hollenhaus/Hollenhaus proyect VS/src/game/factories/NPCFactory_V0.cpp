#include <../pchs/pch.h>

#include "NPCFactory_V0.h"
#include "../components/NPC.h"
#include "../components/ShineComponent.h"
#include "../components/FadeComponent.h"
#include "../gamestates/GameState.h"

ecs::entity_t NPCFactory_V0::createNPC(JsonData::NPCData info, ecs::entity_t parent, int convo)
{
	ecs::entity_t npc = Instantiate();
	npc->addComponent<Transform>();

	npc->addComponent<SpriteRenderer>(info.getSprite());
	npc->addComponent<BoxCollider>();

	npc->getComponent<Transform>()->addParent(parent->getComponent<Transform>());
	npc->getComponent<Transform>()->getRelativeScale().set(info.getScale().getX(), info.getScale().getY());
	Vector2D pos;
	if(info.getSprite() != "tfno"){
		pos = { GameStateMachine::instance()->getCurrentState()->getLastPaulPos().getX() + info.getPos().getX(), info.getPos().getY() };
	}
	else {
		pos = { info.getPos().getX(), info.getPos().getY() };
	}
	npc->getComponent<Transform>()->setGlobalPos(pos);

	npc->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc->addComponent<NPC>(info.getScene(), info.getType(), info.getName(), info.getID(),convo, true, true);
	npc->setLayer(info.getLayer());

	npc->addComponent<ShineComponent>();
	npc->getComponent<ShineComponent>()->addEnt(npc->getComponent<SpriteRenderer>(), info.shine());

	npc->addComponent<FadeComponent>();

    return npc;
}
