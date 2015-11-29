#include "settings.h"

int Settings::GetFreezeTime() const {
	return freezeTime;
}

int Settings::GetRoundTime() const {
	return roundTime;
}

int Settings::GetTowerVictoryHeight() const {
	return towerVictoryHeight;
}

int Settings::GetMetalVictoryAmount() const {
	return metalVictoryAmount;
}

int Settings::GetStoneVictoryAmount() const {
	return stoneVictoryAmount;
}

void Settings::SetFreezeTime(int _freezeTime) {
	freezeTime = _freezeTime;
}

void Settings::SetRoundTime(int _roundTime) {
	roundTime = _roundTime;
}

void Settings::SetTowerVictoryHeight(int _towerVictoryHeight) {
	towerVictoryHeight = _towerVictoryHeight;
}

void Settings::SetMetalVictoryAmount(int _metalVictoryAmount) {
	metalVictoryAmount = _metalVictoryAmount;
}

void Settings::SetStoneVictoryAmount(int _stoneVictoryAmount) {
	stoneVictoryAmount = _stoneVictoryAmount;
}