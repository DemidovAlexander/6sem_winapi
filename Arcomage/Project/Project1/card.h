#pragma once

#include <string>

struct Card {
	int requiredStoneAmount;
	int requiredMetalAmount;

	int damage;
	int damageEnemyTower;
	int damageYourself;

	int changeYourTower;
	int changeYourWall;

	int changeEnemyMinesNumber;
	int changeEnemyQuarriesNumber;
	int changeYourMinesNumber;
	int changeYourQuarriesNumber;

	int changeEnemyStoneAmount;
	int changeEnemyMetalAmount;
	int changeYourStoneAmount;
	int changeYourMetalAmount;

	std::string name;
};