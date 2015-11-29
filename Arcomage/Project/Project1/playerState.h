#pragma once

#include "Card.h"

class PlayerState {
public:
	PlayerState(bool _isAuto);
	~PlayerState();

	int GetTowerHeight() const;

	int GetWallHeight() const;

	int GetMinesNumber() const;

	int GetQuarriesNumber() const;

	int GetStoneAmount() const;

	int GetMetalAmount() const;

	bool GetCanMove() const;

	bool GetLastCardWasDropped() const;

	void ChangeTowerHeight(int modifier);

	void ChangeWallHeight(int modifier);

	void ChangeMinesNumber(int modifier);

	void ChangeQuarriesNumber(int modifier);

	void ChangeStoneAmount(int modifier);

	void ChangeMetalAmount(int modifier);

	void SetCanMove(bool _canMove);

	void SetLastCardWasDropped(bool flag);

	void SetLastUsedCard(Card card);

	bool IsAuto() const;

	Card GetLastUsedCard();

	bool IsCardAvailable(const Card &card) const;

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
