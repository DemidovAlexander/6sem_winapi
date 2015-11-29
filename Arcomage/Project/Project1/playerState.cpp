#include <windows.h>
#include "cardInHandState.h"
#include "playerState.h"
#include "card.h"

PlayerState::PlayerState(bool isAuto) :
		towerHeight(25),
		wallHeight(10),
		minesNumber(1),
		quarriesNumber(1),
		stoneAmount(2),
		metalAmount(2),
		canMove(!isAuto),
		isAuto(isAuto)
{
}

PlayerState::~PlayerState() 
{
}

int PlayerState::GetTowerHeight() const {
	return towerHeight;
}

int PlayerState::GetWallHeight() const {
	return wallHeight;
}

int PlayerState::GetMinesNumber() const {
	return minesNumber;
}

int PlayerState::GetQuarriesNumber() const {
	return quarriesNumber;
}

int PlayerState::GetStoneAmount() const {
	return stoneAmount;
}

int PlayerState::GetMetalAmount() const {
	return metalAmount;
}

bool PlayerState::GetCanMove() const {
	return canMove;
}

bool PlayerState::GetLastCardWasDropped() const {
	return lastCardWasDropped;
}

void PlayerState::ChangeTowerHeight(int modifier) {
	towerHeight += modifier;
}

void PlayerState::ChangeWallHeight(int modifier) {
	wallHeight += modifier;
}

void PlayerState::ChangeMinesNumber(int modifier) {
	minesNumber += modifier;
}

void PlayerState::ChangeQuarriesNumber(int modifier) {
	quarriesNumber += modifier;
}

void PlayerState::ChangeStoneAmount(int modifier) {
	stoneAmount += modifier;
}

void PlayerState::ChangeMetalAmount(int modifier) {
	metalAmount += modifier;
}

void PlayerState::SetCanMove(bool _canMove) {
	canMove = _canMove;
}

void PlayerState::SetLastUsedCard(Card card) {
	lastUsedCard = card;
}

void PlayerState::SetLastCardWasDropped(bool flag) {
	lastCardWasDropped = flag;
}

bool PlayerState::IsAuto() const {
	return isAuto;
}

void PlayerState::UpdateResources() {
	metalAmount += minesNumber;
	stoneAmount += quarriesNumber;
}

Card PlayerState::GetLastUsedCard() {
	return lastUsedCard;
}

bool PlayerState::IsCardAvailable(const Card &card) const {
	return ((card.requiredMetalAmount <= GetMetalAmount()) 
		&& (card.requiredStoneAmount <= GetStoneAmount()));
}