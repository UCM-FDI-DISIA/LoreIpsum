#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include "Transform.h"
#include "BoxCollider.h"

class HandComponent :
	public ComponentUpdate
{
public:
	HandComponent();
	//~HandComponent();

	void initComponent() override;
	void update() override;

	/// <summary>
	/// Anade una carta a la mano.
	/// </summary>
	void addCard(ecs::entity_t* card);

	/// <summary>
	/// Saca una carta de
	/// </summary>
	void removeCard(ecs::entity_t card);

private:
	//void removeParent();

	// Transform de la mano
	Transform* transform;
	// Collider de la mano
	BoxCollider* collider;

	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsParents;
	std::vector<ecs::entity_t*> cardsInHand;
};