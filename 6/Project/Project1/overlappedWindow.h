#pragma once

#include <windows.h>
#include "windowSettings.h"

class COverlappedWindow {
public:
	WindowSettings settings;
	HBRUSH backgroundBrush;

    COverlappedWindow();
    ~COverlappedWindow();

    // Зарегистрировать класс окна
    static bool RegisterClass(HINSTANCE hInstance);

    // Создать экземпляр окна
    bool Create(HINSTANCE hInstance, int cmdShow);

    // Показать окно
    void Show();	
	void CreateDialogWindow(int cmdShow);
	void ApplySettings();

	HWND GetHandle();
	HWND GetEditControlHandle();
	HWND GetDialogHandle();

protected:
    void OnDestroy();
	void OnSize();
	void OnClose();
	void OnCommand(WPARAM wParam);
	LRESULT OnCtlcoloredit(WPARAM wParam);

	bool Save();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // хэндл окна
	HWND editControlHandle; // хэндл edit control
	HWND dialogHandle; // хэндл диалогового окна

	int cmdShow;

	bool wasChanged;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
