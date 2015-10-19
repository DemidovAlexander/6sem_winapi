#pragma once

#include <vector>

#include "cardInHandState.h"
#include "playerState.h"

class PlayerHandState {
public:
	PlayerHandState(CardsDeckState* _cardsDeckState, PlayerState* _playerState, PlayerState* _enemyPlayerState);
	~PlayerHandState();

	std::vector<CardInHandState> cardInHandStates;
};