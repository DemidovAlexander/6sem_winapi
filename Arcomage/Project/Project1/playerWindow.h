#pragma once

#include <windows.h>

#include "PlayerState.h"
#include "settings.h"

class PlayerWindow {
public:
	bool repainted;

	PlayerWindow(PlayerState* _playerState, Settings* _settings);
	~PlayerWindow();

	// ���������������� ����� ����
	static bool RegisterClass(HINSTANCE hInstance);

	// ������� ��������� ����
	bool Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow);

	// �������� ����
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