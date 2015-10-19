#include "AIPlayer.h"
#include <iostream>
#include <time.h>

AIPlayer::AIPlayer(PlayerHandState* _playerHandState) :
	playerHandState(_playerHandState)
{
}

AIPlayer::~AIPlayer()
{
}

int AIPlayer::countCardValue(Card &card) {
	return 0;
}