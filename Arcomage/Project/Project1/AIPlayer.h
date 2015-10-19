#pragma once

#include "card.h"
#include "playerHandState.h"

class AIPlayer {
public:
	PlayerHandState* playerHandState;

	AIPlayer(PlayerHandState* _playerHandState);
	~AIPlayer();

	int countCardValue(Card &card);
};