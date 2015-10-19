#pragma once

#include <windows.h>
#include <vector>

#include "playerHandState.h"
#include "cardInHandWindow.h"

class PlayerInterfaceWindow {
public:
	PlayerInterfaceWindow(PlayerHandState* _playerHandState);
	~PlayerInterfaceWindow();

	// ���������������� ����� ����
	static bool RegisterClass(HINSTANCE hInstance);

	// ������� ��������� ����
	bool Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow);

	// �������� ����
	void Show();

	HWND GetHandle();

	void dropCardInHand(int number);

protected:
	void OnDestroy();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	HWND handle;
	int cmdShow;

	std::vector<CardInHandWindow> cardInHandWindows;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
