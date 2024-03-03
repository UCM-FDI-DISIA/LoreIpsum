#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include "Transform.h"
#include "BoxCollider.h"

const unsigned int	MAX_HAND_CARDS = 7,
					CARD_SEPARATION = 30,
					ARCH_AMPLITUDE=1000;

class Card;

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
	/// <param name="card">Carta a anadir</param>
	/// <returns>Si ha anadido la carta devuelve true, si no false.</returns>
	bool addCard(ecs::entity_t card);

	/// <summary>
	/// Saca una carta de
	/// </summary>
	void removeCard(ecs::entity_t card);

private:
	void refreshPositions();

	// Transform de la mano
	Transform* transform_;
	// Collider de la mano
	//BoxCollider* collider;

	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsInHand_;
};