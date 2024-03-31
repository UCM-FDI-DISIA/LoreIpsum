#include "pch.h"
#include "NPCFactory_V0.h"
#include "../components/NPC.h"

ecs::entity_t NPCFactory_V0::createNPC(JsonData::NPCData info, ecs::entity_t parent)
{
	ecs::entity_t npc = Instantiate();
	npc->addComponent<Transform>();
	npc->addComponent<SpriteRenderer>(info.getSprite());
	npc->addComponent<BoxCollider>();
	npc->getComponent<Transform>()->addParent(parent->getComponent<Transform>());
	npc->getComponent<Transform>()->getRelativeScale().set(info.getScale().getX(), info.getScale().getY());
	Vector2D pos{ info.getPos().getX(), info.getPos().getY() };
	npc->getComponent<Transform>()->setGlobalPos(pos);
	npc->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc->addComponent<NPC>(info.getScene());
	npc->setLayer(info.getLayer());

    return npc;
}