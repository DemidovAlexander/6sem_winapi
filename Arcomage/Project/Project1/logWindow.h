#pragma once

#include <windows.h>

#include "card.h"

class LogWindow {
public:
	HBRUSH backgroundBrush;

	LogWindow();
	~LogWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create(HINSTANCE hInstance, HWND parentHandle, int cmdShow);

	// Показать окно
	void Show();

	HWND GetHandle();
	HWND GetLogHandle();

	void PrintTimeIsOutMessage();

	void PrintChooseCardMessage(int remainingTime);

	void PrintEnemyMove();

	void PrintVictoryText();

	void PrintLossText();

	void PrintCardLog(Card &card, bool wasDropped);

protected:
	void OnDestroy();
	LRESULT OnCtlcolorstatic(WPARAM wParam);

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 
	static wchar_t* initialText;
	static wchar_t* timeIsOutText;
	static wchar_t* enemyMoveText;

	static wchar_t* victoryText;
	static wchar_t* lossText;

	static std::string chooseCardText;

	UINT printLogMessage;

	HWND handle;
	HWND logHandle;

	int cmdShow;

	COLORREF currentBackgroundColor;
	COLORREF standardBackgroundColor;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};

