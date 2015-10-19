#pragma once

#include <windows.h>

#include "PlayerState.h"
#include "settings.h"

class PlayerWindow {
public:
	bool repainted;

	PlayerWindow(PlayerState* _playerState, Settings* _settings);
	~PlayerWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow);

	// Показать окно
	void Show();

	HWND GetHandle();

protected:
	void OnDestroy();
	void OnPaint();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	int cmdShow;

	HWND handle;

	PlayerState* playerState;
	Settings* settings;

	void drawBuildings(HDC dc);
	void drawStats(HDC dc);

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};