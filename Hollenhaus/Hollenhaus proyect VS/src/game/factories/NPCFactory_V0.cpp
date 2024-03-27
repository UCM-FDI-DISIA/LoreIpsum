#include "pch.h"
#include "NPCFactory_V0.h"
#include "../components/NPC.h"

ecs::entity_t NPCFactory_V0::createNPC(std::string id, std::string sprite,
	Vector2D scale, Vector2D pos, int type, int scene, int layer,
	ecs::entity_t parent)
{
	ecs::entity_t npc = Instantiate();
	npc->addComponent<Transform>();
	npc->addComponent<SpriteRenderer>(sprite);
	npc->addComponent<BoxCollider>();
	npc->getComponent<Transform>()->addParent(parent->getComponent<Transform>());
	npc->getComponent<Transform>()->getRelativeScale().set(scale.getX(), scale.getY());
	npc->getComponent<Transform>()->setGlobalPos(pos);
	npc->getComponent<BoxCollider>()->setAnchoredToSprite(true);
	npc->addComponent<NPC>(scene); // Lleva a la oficina (2).
	npc->setLayer(layer);

    return npc;
}
