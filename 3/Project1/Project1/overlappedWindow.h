#pragma once

#include <windows.h>
#include "ellipseWindow.h"

class COverlappedWindow {
public:
    COverlappedWindow();
    ~COverlappedWindow();

    // Зарегистрировать класс окна
    static bool RegisterClass(HINSTANCE hInstance);

    // Создать экземпляр окна
    bool Create(HINSTANCE hInstance);

    // Показать окно
    void Show( int cmdShow );

protected:
    void OnDestroy();
	void OnSize();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // хэндл окна

	CEllipseWindow leftTop;
	CEllipseWindow rightTop;
	CEllipseWindow leftBottom;
	CEllipseWindow rightBottom;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
