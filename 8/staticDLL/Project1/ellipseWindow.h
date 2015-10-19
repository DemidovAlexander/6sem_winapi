#pragma once

#include "ellipse.h"
#include <windows.h>

class CEllipseWindow {
public:
	CEllipseWindow();
	~CEllipseWindow();

	// ���������������� ����� ����
	static bool RegisterClass(HINSTANCE hInstance);

	// ������� ��������� ����
	bool Create(HINSTANCE hInstance, HWND parentHandle, int id);

	// �������� ����
	void Show(int cmdShow);

	HWND getHandle();

protected:
	void onDestroy();
	void onPaint();
	void onTimer();
	void onClick();
	void onSize();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	HWND handle; // ����� ����
	UINT timerID;

	�Ellipse ellipse;
	void drawEllipse(HDC dc);

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};