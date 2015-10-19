#pragma once

#include <deque>

#include "card.h"
#include "cardsDeckState.h"


class CardsDeckState {
public:
	CardsDeckState(int _cardsNumber);
	~CardsDeckState();

	void ReturnCard(Card card);
	Card GetCard();

private:
	std::deque<Card> cards;
};