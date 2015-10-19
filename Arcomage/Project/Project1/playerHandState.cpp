#include "playerHandState.h"
#include "cardsDeckState.h"
#include "playerState.h"

PlayerHandState::PlayerHandState(CardsDeckState* cardsDeckState, PlayerState* playerState, PlayerState* enemyPlayerState)
{
	for (int i = 0; i < 5; ++i) {
		cardInHandStates.push_back(CardInHandState(cardsDeckState, playerState, enemyPlayerState));
	}
}

PlayerHandState::~PlayerHandState()
{ 
}