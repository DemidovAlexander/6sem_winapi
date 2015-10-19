#pragma once

class Settings {
public:
	int GetFreezeTime();
	int GetRoundTime();

	int GetTowerVictoryHeight();
	int GetMetalVictoryAmount();
	int GetStoneVictoryAmount();

	void SetFreezeTime(int _freezeTime);
	void SetRoundTime(int _roundTime);

	void SetTowerVictoryHeight(int _towerVictoryHeight);
	void SetMetalVictoryAmount(int _metalVictoryAmount);
	void SetStoneVictoryAmount(int _stoneVictoryAmount);

private:
	int freezeTime;
	int roundTime;
	int towerVictoryHeight;
	int	metalVictoryAmount;
	int	stoneVictoryAmount;
};