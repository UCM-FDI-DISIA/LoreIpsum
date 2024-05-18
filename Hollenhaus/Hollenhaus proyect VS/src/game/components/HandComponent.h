#pragma once

//Checkml
#include <game/checkML.h>

#include "ComponentUpdate.h"
#include <vector>
#include "basics/Transform.h"
#include "../../utils/tweeny-3.2.0.h"
#include <array>

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

	void update() override;

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

	// devuelve si las animaciones de robar estan hechas
	bool doneDrawAnimations() { return !tweenCardRob; }

	// devuelve si las animaciones de colocar estan hechas
	bool donePosAnimations() { return !tweenCardRob; }

	//para la IA
	std::vector<Card*> getHand();

	//para multiplayer

	int indexOf(ecs::entity_t c);

private:
	float cardScale_ = 0.65f;
	float cardScaleBoard_ = 0.53f;
	
	void refreshPositions();

	// Transform de la mano
	Transform* transform_;
	// Collider de la mano
	//BoxCollider* collider;

	// Vector cartas en la mano
	std::vector<ecs::entity_t> cardsInHand_;
	std::vector<Vector2D> cardPositions_;

	ecs::entity_t lastCardAdded_; // Para order in layer

	/// movidas que estoy haciendo para girar el mazo al segundo jugador
	bool downwards_ = true;
	Players::Owner owner_;

	//Cosas del tween
	// Tweens robar carta
	std::array<tweeny::tween<float>,7 >tweenDrawCardX;
	std::array<tweeny::tween<float>,7 >tweenDrawCardY;
	// Tweens colocar en el tablero
	std::array<tweeny::tween<float>,7 >tweenPosCardX;
	std::array<tweeny::tween<float>,7 >tweenPosCardY;

	ecs::entity_t carta;
	bool tweenCardRob = false;
	bool tweenCardPos = false;
};