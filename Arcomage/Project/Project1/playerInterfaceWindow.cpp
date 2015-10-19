#include <windows.h>
#include "playerInterfaceWindow.h"
#include "cardInHandWindow.h"
#include "playerHandState.h"

PlayerInterfaceWindow::PlayerInterfaceWindow(PlayerHandState* playerHandState) :
	handle(0)
{
	for (int i = 0; i < 5; ++i) {
		cardInHandWindows.push_back(CardInHandWindow(&((*playerHandState).cardInHandStates[i])));
	}
}

PlayerInterfaceWindow::~PlayerInterfaceWindow()
{
}

wchar_t* PlayerInterfaceWindow::nameClassWindow = L"classPlayerInterfaceWindow";
wchar_t* PlayerInterfaceWindow::nameWindow = L"playerInterfaceWindow";

bool PlayerInterfaceWindow::RegisterClass(HINSTANCE hInstance) {
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

bool PlayerInterfaceWindow::Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow) {
	cmdShow = nCmdShow;

	handle = CreateWindow( nameClassWindow, nameWindow, WS_CHILD | WS_BORDER | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, parentHandle, NULL, hInstance, this );	

	if (handle == NULL) {
		::MessageBox( handle, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	for (int i = 0; i < 5; ++i) {
		cardInHandWindows[i].Create( hInstance, handle, cmdShow, i);
	}

	return true;	
}

HWND PlayerInterfaceWindow::GetHandle() {
	return handle;
}

void PlayerInterfaceWindow::dropCardInHand(int number) {
	cardInHandWindows[number].dropCardInHand();
}

void PlayerInterfaceWindow::Show() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		for (int i = 0; i < 5; ++i) {
			::SetWindowPos( cardInHandWindows[i].GetHandle(), NULL, i * width / 5, 0, width / 5 - 1, height, 0);
		}
	}

	for (int i = 0; i < 5; ++i) {
		cardInHandWindows[i].Show();
	}

	::UpdateWindow(handle);
	::ShowWindow( handle, cmdShow );
}

void PlayerInterfaceWindow::OnDestroy() {
	::PostQuitMessage( 0 );	
}

LRESULT __stdcall PlayerInterfaceWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		PlayerInterfaceWindow* that = reinterpret_cast< PlayerInterfaceWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		::SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return ::DefWindowProc( handle, message, wParam, lParam ); 
	} 

	PlayerInterfaceWindow* that = reinterpret_cast< PlayerInterfaceWindow* >( ::GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;	
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}