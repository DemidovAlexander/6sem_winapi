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
    void Show( int cmdShow );

protected:
    void onDestroy();
	void onSize();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

    HWND handle; // ����� ����

	CEllipseWindow leftTop;
	CEllipseWindow rightTop;
	CEllipseWindow leftBottom;
	CEllipseWindow rightBottom;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};
