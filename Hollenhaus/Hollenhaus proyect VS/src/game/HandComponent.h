#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include "Transform.h"
#include "BoxCollider.h"

const int	
					CARD_SEPARATION = 50,
					ARCH_AMPLITUDE	= 750;

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

	/// movidas para J2
	void setUpwards()	{ downwards_ = false; }
	void setDownwards() { downwards_ = true; }
	void setOwner(Players::Owner value) { owner_ = value;}
	Players::Owner getOwner() const { return owner_; }

private:
	float cardScale_ = 0.45f;
	
	void refreshPositions();

	// Transform de la mano
	Transform* transform_;
	// Collider de la mano
	//BoxCollider* collider;

	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsInHand_;

	/// movidas que estoy haciendo para girar el mazo al segundo jugador
	bool downwards_ = true;
	Players::Owner owner_;
};