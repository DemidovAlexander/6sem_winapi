#pragma once

#include <algorithm>

#include "card.h"
#include "cardsDeckState.h"
#include "playerState.h"


class CardInHandState {
public:
	CardInHandState(CardsDeckState &_cardsDeckState, PlayerState &_playerState, PlayerState &_enemyPlayerState);
	~CardInHandState();

	void ApplyCard();
	void DropCard();

	const Card& GetCard() const;

	const PlayerState& GetPlayerState() const;

private:
	Card card;

	PlayerState& playerState;

	CardsDeckState& cardsDeckState;
	PlayerState& enemyPlayerState;
};