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
	bool Create( HINSTANCE hInstance, HWND parentHandle, int cmdShow );

	// Показать окно
	void Show();

	HWND GetHandle() const;
	HWND GetLogHandle() const;

	void PrintTimeIsOutMessage();

	void PrintChooseCardMessage(int remainingTime);

	void PrintEnemyMove();

	void PrintVictoryText();

	void PrintLossText();

	void PrintCardLog(const Card &card, bool wasDropped);

protected:
	LRESULT OnCtlcolorstatic(WPARAM wParam);

private:
	const static wchar_t* nameClassWindow; 
	const static wchar_t* nameWindow;
	const static wchar_t* initialText;
	const static wchar_t* timeIsOutText;
	const static wchar_t* enemyMoveText;

	const static wchar_t* victoryText;
	const static wchar_t* lossText;

	const static std::string chooseCardText;

	UINT printLogMessage;

	HWND handle;
	HWND logHandle;

	int cmdShow;

	COLORREF currentBackgroundColor;
	const COLORREF standardBackgroundColor;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};

