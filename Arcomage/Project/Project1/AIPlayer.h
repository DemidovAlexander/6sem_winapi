#pragma once

#include "card.h"
#include "playerState.h"
#include "playerHandState.h"
#include "settings.h"

class AIPlayer {
public:
	AIPlayer(PlayerHandState &_playerHandState, PlayerState &_playerState, PlayerState &_enemyPlayerState, Settings &_settings);
	~AIPlayer();

	void Move();

private:
	int countCardValue(const Card &card) const;

	PlayerState& playerState;
	PlayerState& enemyPlayerState;

	PlayerHandState& playerHandState;

	Settings& settings;
};