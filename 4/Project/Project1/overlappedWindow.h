#pragma once

#include <windows.h>
#include "ellipseWindow.h"

class COverlappedWindow {
public:
    COverlappedWindow();
    ~COverlappedWindow();

    // ���������������� ����� ����
    static bool RegisterClass(HINSTANCE hInstance);

    // ������� ��������� ����
    bool Create(HINSTANCE hInstance);

    // �������� ����
    void Show(int cmdShow);

protected:
    void OnDestroy();
	void OnSize();
	void OnClose();
	void OnCommand(WPARAM wParam);

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // ����� ����
	HWND editControlHandle; // ����� edit control

	bool wasChanged;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
