#pragma once

#include <windows.h>
#include <vector>

#include "playerHandState.h"
#include "cardInHandWindow.h"

class PlayerInterfaceWindow {
public:
	PlayerInterfaceWindow(PlayerHandState &_playerHandState);
	~PlayerInterfaceWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create( HINSTANCE hInstance, HWND parentHandle, int nCmdShow );

	// Показать окно
	void Show();

	HWND GetHandle() const;

	void DropCardInHand(int number);

private:
	const static wchar_t* nameClassWindow; 
	const static wchar_t* nameWindow; 

	HWND handle;
	int cmdShow;

	std::vector<CardInHandWindow> cardInHandWindows;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
