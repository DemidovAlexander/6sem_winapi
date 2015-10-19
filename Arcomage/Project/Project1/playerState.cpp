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

int PlayerState::GetTowerHeight() {
	return towerHeight;
}

int PlayerState::GetWallHeight() {
	return wallHeight;
}

int PlayerState::GetMinesNumber() {
	return minesNumber;
}

int PlayerState::GetQuarriesNumber() {
	return quarriesNumber;
}

int PlayerState::GetStoneAmount() {
	return stoneAmount;
}

int PlayerState::GetMetalAmount() {
	return metalAmount;
}

bool PlayerState::GetCanMove() {
	return canMove;
}

bool PlayerState::GetLastCardWasDropped() {
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

bool PlayerState::IsAuto() {
	return isAuto;
}

void PlayerState::UpdateResources() {
	metalAmount += minesNumber;
	stoneAmount += quarriesNumber;
}

Card PlayerState::GetLastUsedCard() {
	return lastUsedCard;
}

bool PlayerState::IsCardAvailable(Card card) {
	return ((card.requiredMetalAmount <= GetMetalAmount()) 
		&& (card.requiredStoneAmount <= GetStoneAmount()));
}