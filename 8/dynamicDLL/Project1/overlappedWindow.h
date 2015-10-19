#pragma once

#include <windows.h>
#include "windowSettings.h"

typedef int(__cdecl *MYPROC)(LPWSTR);

class COverlappedWindow {
public:
	WindowSettings settings;
	HBRUSH backgroundBrush;

    COverlappedWindow();
    ~COverlappedWindow();

    // ���������������� ����� ����
    static bool RegisterClass(HINSTANCE hInstance);

    // ������� ��������� ����
    bool Create(HINSTANCE hInstance, int cmdShow);

    // �������� ����
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
	void OnCountWords();
	LRESULT OnCtlcoloredit(WPARAM wParam);

	bool Save();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // ����� ����
	HWND editControlHandle; // ����� edit control
	HWND dialogHandle; // ����� ����������� ����

	HINSTANCE hinstLib;
	MYPROC WordsCount;

	int cmdShow;

	bool wasChanged;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
