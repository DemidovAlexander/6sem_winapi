#pragma once

#include <windows.h>

#include "PlayerState.h"
#include "settings.h"

class PlayerWindow {
public:
	bool repainted;

	PlayerWindow( PlayerState &_playerState, const Settings &_settings );
	~PlayerWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create( HINSTANCE hInstance, HWND parentHandle, int nCmdShow );

	// Показать окно
	void Show();

	HWND GetHandle() const;

protected:
	void OnPaint();

private:
	const static wchar_t* nameClassWindow; 
	const static wchar_t* nameWindow; 

	int cmdShow;

	HWND handle;

	PlayerState& playerState;
	const Settings& settings;

	void drawBuildings(HDC dc) const;
	void drawStats(HDC dc) const;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};