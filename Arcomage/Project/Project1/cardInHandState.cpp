#pragma once

#include "cardInHandState.h"

CardInHandState::CardInHandState(CardsDeckState* _cardsDeckState, PlayerState* _playerState, PlayerState* _enemyPlayerState) :
	cardsDeckState(_cardsDeckState),
	playerState(_playerState),
	enemyPlayerState(_enemyPlayerState)
{
	card = cardsDeckState->GetCard();
}

CardInHandState::~CardInHandState() 
{
}

void CardInHandState::ApplyCard() {
	playerState->SetCanMove(false);
	playerState->SetLastCardWasDropped(false);
	playerState->SetLastUsedCard(card);

	playerState->ChangeTowerHeight(card.changeYourTower - card.damageYourself + std::min(playerState->GetWallHeight(), card.damageYourself));
	playerState->ChangeWallHeight(-std::min(playerState->GetWallHeight(), card.damageYourself) + card.changeYourWall);
	playerState->ChangeMinesNumber(card.changeYourMinesNumber);
	playerState->ChangeQuarriesNumber(card.changeYourQuarriesNumber);
	playerState->ChangeStoneAmount(card.changeYourStoneAmount - card.requiredStoneAmount);
	playerState->ChangeMetalAmount(card.changeYourMetalAmount - card.requiredMetalAmount);

	enemyPlayerState->ChangeTowerHeight(-card.damageEnemyTower - card.damage + std::min(enemyPlayerState->GetWallHeight(), card.damage));
	enemyPlayerState->ChangeWallHeight(-std::min(enemyPlayerState->GetWallHeight(), card.damage));
	enemyPlayerState->ChangeMinesNumber(card.changeEnemyMinesNumber);
	enemyPlayerState->ChangeQuarriesNumber(card.changeEnemyQuarriesNumber);
	enemyPlayerState->ChangeStoneAmount(card.changeEnemyStoneAmount);
	enemyPlayerState->ChangeMetalAmount(card.changeEnemyMetalAmount);

	cardsDeckState->ReturnCard(card);
	card = cardsDeckState->GetCard();
}

void CardInHandState::DropCard() {
	playerState->SetCanMove(false);
	playerState->SetLastCardWasDropped(true);
	playerState->SetLastUsedCard(card);
		
	cardsDeckState->ReturnCard(card);
	card = cardsDeckState->GetCard();
}