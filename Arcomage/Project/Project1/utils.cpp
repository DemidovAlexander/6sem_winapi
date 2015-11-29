#include <windows.h>
#include <string>

#include "utils.h"


int GetPixelSize(int fontSize) {
	HDC dc = ::GetDC(NULL);
	int pexelsy = ::GetDeviceCaps(dc, LOGPIXELSY);
	::DeleteDC(dc);
	return ::MulDiv(fontSize, pexelsy, 36);
}

void PrintCard(HWND staticHandle, const Card &card, bool wasDropped) {
	std::string text = "";

	if (wasDropped) {
		text += "DROPPED\n\n";
	}

	text += card.name + '\n';

	if (card.requiredStoneAmount > 0) {
		text += "\nRequired stone: ";
		text += std::to_string(card.requiredStoneAmount);
	}

	if (card.requiredMetalAmount > 0) {
		text += "\nRequired metal: ";
		text += std::to_string(card.requiredMetalAmount);
	}

	text += "\n\n";
	if ((card.requiredStoneAmount <= 0) || (card.requiredMetalAmount <= 0)) {
		text += "\n\n";
	}

	if (card.damage != 0) {
		text += "\nDamage: ";
		text += std::to_string(card.damage);
	}

	if (card.damageEnemyTower != 0) {
		text += "\nDamage enemy tower: ";
		text += std::to_string(card.damageEnemyTower);
	}

	if (card.damageYourself != 0) {
		text += "\nDamage to you: ";
		text += std::to_string(card.damageYourself);
	}

	if (card.changeYourTower != 0) {
		text += "\nTower: ";
		text += std::to_string(card.changeYourTower);
	}

	if (card.changeYourWall != 0) {
		text += "\nWall: ";
		text += std::to_string(card.changeYourWall);
	}

	if (card.changeEnemyMinesNumber != 0) {
		text += "\nEnemy mines: ";
		text += std::to_string(card.changeEnemyMinesNumber);
	}

	if (card.changeEnemyQuarriesNumber != 0) {
		text += "\nEnemy quarries: ";
		text += std::to_string(card.changeEnemyQuarriesNumber);
	}

	if (card.changeYourMinesNumber != 0) {
		text += "\nMines: ";
		text += std::to_string(card.changeYourMinesNumber);
	}

	if (card.changeYourQuarriesNumber != 0) {
		text += "\nQuarries: ";
		text += std::to_string(card.changeYourQuarriesNumber);
	}

	if (card.changeEnemyStoneAmount != 0) {
		text += "\nEnemy stone: ";
		text += std::to_string(card.changeEnemyStoneAmount);
	}

	if (card.changeEnemyMetalAmount != 0) {
		text += "\nEnemy metal: ";
		text += std::to_string(card.changeEnemyMetalAmount);
	}

	if (card.changeYourStoneAmount != 0) {
		text += "\nStone: ";
		text += std::to_string(card.changeYourStoneAmount);
	}

	if (card.changeYourMetalAmount != 0) {
		text += "\nMetal: ";
		text += std::to_string(card.changeYourMetalAmount);
	}

	::SetWindowText( staticHandle, (LPCWSTR)std::wstring(text.begin(), text.end()).c_str() );
}

COLORREF GetCardColor(const Card &card) {
	if (card.requiredMetalAmount > 0) {
		if (card.requiredStoneAmount > 0) {
			return RGB(255, 211, 155);
		}

		return RGB(245, 245, 220);
	}

	return RGB(255, 236, 139);
}