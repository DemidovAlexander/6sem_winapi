#include <windows.h>
#include "overlappedWindow.h"

COverlappedWindow::COverlappedWindow() :
	handle(0)
{
}

COverlappedWindow::~COverlappedWindow()
{
}

wchar_t* COverlappedWindow::nameClassWindow = L"ClassOverlappedWindow";
wchar_t* COverlappedWindow::nameWindow = L"OverlappedWindow";

bool COverlappedWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = CS_HREDRAW | CS_VREDRAW;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	tag.hCursor = LoadCursor(NULL, IDC_ARROW);
	tag.hbrBackground =  (HBRUSH)GetStockObject(WHITE_BRUSH);
	tag.lpszMenuName = NULL;
	tag.lpszClassName = nameClassWindow;
	tag.hInstance = hInstance;
	tag.hIconSm = NULL;

	if ( !RegisterClassEx(&tag) ) {
		MessageBox( NULL, L"Can't register class", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;
}

bool COverlappedWindow::Create(HINSTANCE hInstance) {
	handle = CreateWindow( nameClassWindow, nameWindow, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, this );	

	if (handle == NULL) {
		MessageBox( NULL, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	leftTop.Create( hInstance, handle, 0 );
	rightTop.Create( hInstance, handle, 1 );
	leftBottom.Create( hInstance, handle, 2 );
	rightBottom.Create( hInstance, handle, 3 );

	return true;	
}

void COverlappedWindow::Show(int cmdShow) {
	UpdateWindow(handle);
	
	leftTop.Show( cmdShow );
	leftBottom.Show( cmdShow );

	rightTop.Show( cmdShow );
	rightBottom.Show( cmdShow );

	ShowWindow( handle, cmdShow );
}

void COverlappedWindow::onDestroy() {
	PostQuitMessage( 0 );	
}

void COverlappedWindow::onSize() {
	RECT rect;
	if (GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		SetWindowPos( leftTop.getHandle(), NULL, 0, 0, width / 2, height / 2, 0 );
		SetWindowPos( leftBottom.getHandle(), NULL, 0, height / 2 + 1, width / 2, height / 2, 0 );

		SetWindowPos( rightTop.getHandle(), NULL, width / 2 + 1, 0, width / 2, height / 2, 0 );
		SetWindowPos( rightBottom.getHandle(), NULL, width / 2 + 1, height / 2 + 1, width / 2, height / 2, 0 );
	}
}

LRESULT __stdcall COverlappedWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		COverlappedWindow* that = reinterpret_cast< COverlappedWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return DefWindowProc( handle, message, wParam, lParam ); 
	} 

	COverlappedWindow* that = reinterpret_cast< COverlappedWindow* >( GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->onDestroy();
			return 0;
		case WM_CLOSE:
			DestroyWindow(handle);
			return 0;
		case WM_SIZE:
			that->onSize();
			return 0;
	}
	return DefWindowProc( handle, message, wParam, lParam );
}