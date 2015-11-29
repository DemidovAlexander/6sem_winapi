#include "AIPlayer.h"
#include <iostream>
#include <time.h>

AIPlayer::AIPlayer(PlayerHandState &_playerHandState, PlayerState &_playerState, PlayerState &_enemyPlayerState,
	Settings &_settings) :

	playerState(_playerState),
	enemyPlayerState(_enemyPlayerState),
	playerHandState(_playerHandState),
	settings(_settings)
{
}

AIPlayer::~AIPlayer()
{
}

void AIPlayer::Move() {
	int bestCardIndex = -1;
	int currentMaxValue = -1;

	for (int i = 0; i < 5; ++i) {
		if (playerHandState.cardInHandStates[i].GetPlayerState().IsCardAvailable(
			playerHandState.cardInHandStates[i].GetCard()))
		{
			int cardValue = countCardValue(playerHandState.cardInHandStates[i].GetCard());
			if (cardValue >= currentMaxValue) {
				currentMaxValue = cardValue;
				bestCardIndex = i;
			}
		}
	}

	if (bestCardIndex >= 0) {
		playerHandState.cardInHandStates[bestCardIndex].ApplyCard();
	} else {
		playerHandState.cardInHandStates[0].DropCard();
	}
}

int AIPlayer::countCardValue(const Card &card) const {
	return 1;
}