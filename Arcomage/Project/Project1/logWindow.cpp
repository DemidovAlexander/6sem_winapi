#include <windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <string>

#include "logWindow.h"
#include "utils.h"

LogWindow::LogWindow() :
	handle(0),
	logHandle(0), 
	backgroundBrush(CreateSolidBrush(RGB(255, 255, 255))),
	currentBackgroundColor(RGB(245, 255, 250)),
	standardBackgroundColor(RGB(245, 255, 250))
{
}

LogWindow::~LogWindow() {
	DeleteObject(backgroundBrush);
}

wchar_t* LogWindow::nameClassWindow = L"ClassLogWindow";
wchar_t* LogWindow::nameWindow = L"LogWindow";
wchar_t* LogWindow::initialText = L"Your game\nis starting now";
wchar_t* LogWindow::timeIsOutText = L"Time is out";
wchar_t* LogWindow::enemyMoveText = L"Enemy's turn\n";

wchar_t* LogWindow::victoryText = L"Victory!\n";
wchar_t* LogWindow::lossText = L"Loss(\n";

std::string LogWindow::chooseCardText = "Choose card\n\n\n\n";


bool LogWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = 0;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	tag.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	tag.hbrBackground =  (HBRUSH)::GetStockObject(WHITE_BRUSH);
	tag.lpszMenuName = NULL;
	tag.lpszClassName = nameClassWindow;
	tag.hInstance = hInstance;
	tag.hIconSm = NULL;

	if ( !::RegisterClassEx(&tag) ) {
		::MessageBox( NULL, L"Can't register class", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;
}

bool LogWindow::Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow) {
	cmdShow = nCmdShow;

	handle = ::CreateWindowEx( NULL, nameClassWindow, NULL, WS_CHILD | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        parentHandle, NULL, hInstance, this );	

	if (handle == NULL) {
		::MessageBox( handle, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	logHandle = ::CreateWindow( L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 0, 0, 0, handle, NULL, hInstance, NULL );

	if (logHandle == NULL) {
		::MessageBox( handle, L"Can't got log handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	LOGFONT logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	logFont.lfHeight = -GetPixelSize(11);
	_tcscpy_s(logFont.lfFaceName, L"Arial");
	HFONT hFont = CreateFontIndirect(&logFont);
	SendMessage(logHandle, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);

	::SetWindowText( logHandle, (LPCWSTR)initialText );

	return true;	
}

void LogWindow::Show() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		::SetWindowPos( logHandle, NULL, 0, 0, width, height, SWP_SHOWWINDOW );
	}

	::UpdateWindow(logHandle);

	::ShowWindow( handle, cmdShow );
	::UpdateWindow(handle);
}

HWND LogWindow::GetHandle() {
	return handle;
}

HWND LogWindow::GetLogHandle() {
	return logHandle;
}

void LogWindow::OnDestroy() {
	PostQuitMessage( 0 );	
}

LRESULT LogWindow::OnCtlcolorstatic(WPARAM wParam) {
	DeleteObject(backgroundBrush);

	SetBkColor((HDC)wParam, currentBackgroundColor);

	backgroundBrush = CreateSolidBrush(currentBackgroundColor);

	return (LRESULT)backgroundBrush;
}

void LogWindow::PrintTimeIsOutMessage() {
	currentBackgroundColor = standardBackgroundColor;
	::SetWindowText( logHandle, (LPCWSTR)timeIsOutText );
}

void LogWindow::PrintChooseCardMessage(int remainingTime) {
	currentBackgroundColor = standardBackgroundColor;

	std::string text = chooseCardText + std::to_string(remainingTime);

	::SetWindowText( logHandle, (LPCWSTR)std::wstring(text.begin(), text.end()).c_str() );
}

void LogWindow::PrintEnemyMove() {
	currentBackgroundColor = standardBackgroundColor;
	::SetWindowText( logHandle, (LPCWSTR)enemyMoveText );
}

void LogWindow::PrintVictoryText() {
	currentBackgroundColor = standardBackgroundColor;
	::SetWindowText( logHandle, (LPCWSTR)victoryText );
}

void LogWindow::PrintLossText() {
	currentBackgroundColor = standardBackgroundColor;
	::SetWindowText( logHandle, (LPCWSTR)lossText );
}

void LogWindow::PrintCardLog(Card& card, bool wasDropped) {
	currentBackgroundColor = GetCardColor(card);
	PrintCard(logHandle, card, wasDropped);
}


LRESULT __stdcall LogWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		LogWindow* that = reinterpret_cast< LogWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		::SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );

		return ::DefWindowProc( handle, message, wParam, lParam ); 
	} 

	LogWindow* that = reinterpret_cast< LogWindow* >( ::GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;
		case WM_CTLCOLORSTATIC:
			return that->OnCtlcolorstatic(wParam);	
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}