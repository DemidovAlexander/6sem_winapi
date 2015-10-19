#pragma once

#include "Card.h"

class PlayerState {
public:
	PlayerState(bool _isAuto);
	~PlayerState();

	int GetTowerHeight();

	int GetWallHeight();

	int GetMinesNumber();

	int GetQuarriesNumber();

	int GetStoneAmount();

	int GetMetalAmount();

	bool GetCanMove();

	bool GetLastCardWasDropped();

	void ChangeTowerHeight(int modifier);

	void ChangeWallHeight(int modifier);

	void ChangeMinesNumber(int modifier);

	void ChangeQuarriesNumber(int modifier);

	void ChangeStoneAmount(int modifier);

	void ChangeMetalAmount(int modifier);

	void SetCanMove(bool _canMove);

	void SetLastCardWasDropped(bool flag);

	void SetLastUsedCard(Card card);

	bool IsAuto();

	Card GetLastUsedCard();

	bool IsCardAvailable(Card card);

	void UpdateResources();

private:
	bool isAuto; // ���� AI ������
	bool canMove; // ������� �� ���������

	int towerHeight; // ������ �����
	int wallHeight; // ������ �����

	int minesNumber; // ���������� ��������
	int quarriesNumber; // ���������� �����������

	int stoneAmount; // ������
	int metalAmount; // ������

	bool lastCardWasDropped;

	Card lastUsedCard;
};
