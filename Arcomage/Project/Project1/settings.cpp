#include "settings.h"

int Settings::GetFreezeTime() {
	return freezeTime;
}

int Settings::GetRoundTime() {
	return roundTime;
}

int Settings::GetTowerVictoryHeight() {
	return towerVictoryHeight;
}

int Settings::GetMetalVictoryAmount() {
	return metalVictoryAmount;
}

int Settings::GetStoneVictoryAmount() {
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