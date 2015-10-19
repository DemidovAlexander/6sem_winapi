#pragma once

#include <algorithm>

#include "card.h"
#include "cardsDeckState.h"
#include "playerState.h"


class CardInHandState {
public:
	Card card;
	PlayerState* playerState;

	CardInHandState(CardsDeckState* _cardsDeckState, PlayerState* _playerState, PlayerState* _enemyPlayerState);
	~CardInHandState();

	void ApplyCard();
	void DropCard();

private:
	CardsDeckState* cardsDeckState;
	PlayerState* enemyPlayerState;
};