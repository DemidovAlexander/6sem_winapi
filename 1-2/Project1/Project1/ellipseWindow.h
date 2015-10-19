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
	bool Create(HINSTANCE hInstance);

	// Показать окно
	void Show(int cmdShow);

protected:
	void onDestroy();
	void onPaint();
	void onTimer();
	void onSize();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	HWND handle; // хэндл окна
	UINT timerID;
	
	CEllipse ellipse;
	void drawEllipse(HDC dc);

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};