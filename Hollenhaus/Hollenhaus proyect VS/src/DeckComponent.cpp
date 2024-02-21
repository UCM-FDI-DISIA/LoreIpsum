#include "DeckComponent.h"

void
DeckComponent::shuffle() {
	// Puede que miki llore con esto no lo se no conozco el coste de estos algoritmos confio en c++
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void 
DeckComponent::removeCard(Card* c) {
	deck.remove(*c);
}

void 
DeckComponent::addCardsOnBottom(std::list<Card> h) {
	while (!h.empty()) {
		deck.push_front(h.front());
		h.pop_front();
	}

	shuffle();
}

Card*
DeckComponent::drawCard() {
	Card* c = &*deck.end();
	removeCard(c);

	return c;
}
