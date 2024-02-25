#pragma once
#include "ComponentUpdate.h"
#include <vector>
#include "Transform.h"
#include "BoxCollider.h"

const unsigned int MAX_HAND_CARDS = 7;

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
	/// <summary>
	/// Metodo para calcular el angulo de una carta en la mano.
	/// </summary>
	/// <param name="numCarta">Numero de carta de izquierda a derecha</param>
	/// <returns>devuelve el angulo de rotacion en grados</returns>
	float calculateAngle(int numCarta);

	// Transform de la mano
	Transform* transform_;
	// Collider de la mano
	//BoxCollider* collider;

	// Cartas en mano
	unsigned int numCards_;
	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsInHand_;
};