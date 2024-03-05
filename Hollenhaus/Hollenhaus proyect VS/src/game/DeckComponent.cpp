#include "DeckComponent.h"

#include <algorithm>
#include <random>
#include "Manager.h"
#include "MatchManager.h"

void
DeckComponent::shuffle() {
	std::random_device rd;
	std::mt19937 rnd(rd());

	// Puede que miki llore con esto no lo se confio en c++
	for (auto i = std::prev(deck.end()); i != deck.begin(); --i) {
		std::uniform_int_distribution<int> u(0, std::distance(deck.begin(), i));
		auto randomIndex = u(rnd);

		std::swap(*i, *std::next(deck.begin(), randomIndex));
	}
}

void
DeckComponent::removeCard(Card* c) {
	deck.remove(c);
}

void
DeckComponent::addCardsOnBottom(std::list<Card*> h) {
	while (!h.empty()) {
		deck.push_front(h.front());
		h.pop_front();
	}

	shuffle();
}

Card*
DeckComponent::drawCard() {
	auto it = deck.end();
	--it;
	Card* c = (*it);
	removeCard(c);
	mngr_->getHandler(ecs::hdlr::MATCH_MANAGER)->getComponent<MatchManager>()->substractActionPoints(drawCardCost);
	
	return c;
}


void 
DeckComponent::addCartToDeck(Card* card) {
	deck.push_back(card);
}