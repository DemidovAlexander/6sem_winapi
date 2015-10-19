#include <windows.h>
#include "ellipseWindow.h"

CEllipseWindow::CEllipseWindow() :
	ellipse(200, 200, 3, 3, 25),
	handle(0)
{
}

CEllipseWindow::~CEllipseWindow() 
{
}

wchar_t* CEllipseWindow::nameClassWindow = L"ClassEllipseWindow";
wchar_t* CEllipseWindow::nameWindow = L"EllipseWindow";

bool CEllipseWindow::RegisterClass(HINSTANCE hInstance) {
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

bool CEllipseWindow::Create(HINSTANCE hInstance, HWND parentHandle, int id) {
	RECT rect;
    GetClientRect( parentHandle, &rect );

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

	int xPosition = 0;
	int yPosition = 0;

	switch( id ) {
	case 0 : 
		xPosition = 0;
		yPosition = 0;
		break;
	case 1:
		xPosition = 0;
		yPosition = height / 2 + 1;
		break;
	case 2:
		xPosition = width / 2 + 1;
		yPosition = 0;
		break;
	case 3:
		xPosition = width / 2 + 1;
		yPosition = height / 2 + 1;
		break;
	}

	handle = CreateWindow( nameClassWindow, nameWindow, WS_CHILD | WS_VISIBLE | WS_BORDER,
        xPosition, yPosition, width / 2, height / 2, parentHandle, NULL, hInstance, this );

    if (handle == NULL) {
		MessageBox( NULL, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;	
}

void CEllipseWindow::Show(int cmdShow) {
	UpdateWindow( handle );
	ShowWindow( handle, cmdShow );
}

HWND CEllipseWindow::getHandle() {
	return handle;
}

void CEllipseWindow::onDestroy() {
	KillTimer( handle, timerID );
	PostQuitMessage( 0 );	
}

void CEllipseWindow::onPaint() {	
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint( handle, &ps );
	HDC newHdc = CreateCompatibleDC(hdc);
	RECT rect;
	GetClientRect(handle, &rect);

	HBITMAP bitmap = CreateCompatibleBitmap( hdc, rect.right - rect.left, rect.bottom - rect.top );
	HGDIOBJ oldbitmap = SelectObject(newHdc, bitmap);

	drawEllipse(newHdc);

	BitBlt( hdc, 0, 0, rect.right, rect.bottom, newHdc, 0, 0, SRCCOPY );
	
	SelectObject(newHdc, oldbitmap);
	DeleteObject(bitmap);

	DeleteDC(hdc);
	DeleteDC(newHdc);

	EndPaint(handle, &ps);
}

void CEllipseWindow::onTimer() {
	RECT rect;
	if (GetClientRect(handle, &rect)) {
		ellipse.moveEllipse();
		InvalidateRect( handle, &rect, false );
	}
}

void CEllipseWindow::onSize() {
	RECT rect;
	if (GetClientRect(handle, &rect)) {
		ellipse.setRect(rect);
		ellipse.moveEllipse();
		InvalidateRect( handle, &rect, false );
	}
}

void CEllipseWindow::onClick() {
	SetFocus(handle);
}

LRESULT __stdcall CEllipseWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		CEllipseWindow* that = reinterpret_cast< CEllipseWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		that->timerID = SetTimer( handle, 0, 1, NULL );
		if (that->timerID == 0) {
			MessageBox( NULL, L"Can't Set Timer", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		}

		return DefWindowProc( handle, message, wParam, lParam ); 
	} 

	CEllipseWindow* that = reinterpret_cast< CEllipseWindow* >( GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->onDestroy();
			return 0;
		case WM_PAINT:
			that->onPaint();
			return 0;
		case WM_TIMER:
			that->onTimer();
			return 0;
		case WM_CLOSE:
			//todo -OnClose
			DestroyWindow(handle);
			return 0;
		case WM_SIZE:
			that->onSize();
			return 0;
		case WM_LBUTTONDOWN:
            that->onClick();
			return 0;
		default:
			return DefWindowProc( handle, message, wParam, lParam );
	}

	
}

void CEllipseWindow::drawEllipse(HDC dc) {
	RECT rect;

	GetClientRect(handle, &rect);

	HBRUSH brush = CreateSolidBrush( RGB( 0, 150, 100) );
	FillRect( dc, &rect, brush );
	DeleteObject(brush);

	ellipse.setRect(rect);
	ellipse.drawEllipse(dc, handle);
}