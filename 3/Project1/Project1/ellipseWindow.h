#pragma once

#include "ellipse.h"
#include <windows.h>

class CEllipseWindow {
public:
	CEllipseWindow();
	~CEllipseWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create( HINSTANCE hInstance, HWND parentHandle, int id );

	// Показать окно
	void Show(int cmdShow);

	HWND GetHandle();

protected:
	void OnDestroy();
	void OnPaint();
	void OnTimer();
	void OnClick();
	void OnSize();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	HWND handle; // хэндл окна
	UINT timerID;

	СEllipse ellipse;
	void drawEllipse(HDC dc);

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};