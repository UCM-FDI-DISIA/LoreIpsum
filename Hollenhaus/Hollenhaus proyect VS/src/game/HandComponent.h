#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include "Transform.h"
#include "BoxCollider.h"

const unsigned int	
					CARD_SEPARATION = 50,
					ARCH_AMPLITUDE=750;

class HandComponent :
	public ComponentUpdate
{
public:
	HandComponent();
	~HandComponent();

	void initComponent() override;

	/// <summary>
	/// Anade una carta a la mano.
	/// </summary>
	/// <param name="card">Carta a anadir</param>
	/// <returns>Si ha anadido la carta devuelve true, si no false.</returns>
	void addCard(ecs::entity_t card);

	/// <summary>
	/// Saca una carta de
	/// </summary>
	void removeCard(ecs::entity_t card);

	int handSize() { return cardsInHand_.size(); }

private:
	float cardScale_ = 0.45f;
	
	void refreshPositions();

	// Transform de la mano
	Transform* transform_;
	// Collider de la mano
	//BoxCollider* collider;

	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsInHand_;
};