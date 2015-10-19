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
    void Show(int cmdShow);

protected:
    void OnDestroy();
	void OnSize();
	void OnClose();
	void OnCommand(WPARAM wParam);

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // хэндл окна
	HWND editControlHandle; // хэндл edit control

	bool wasChanged;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
