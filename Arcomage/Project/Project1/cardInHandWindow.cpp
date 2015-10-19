#include <windows.h>
#include <CommCtrl.h>
#include <tchar.h>

#include "cardInHandWindow.h"
#include "utils.h"

CardInHandWindow::CardInHandWindow(CardInHandState* _cardInHandState) :
	cardInHandState(_cardInHandState),
	backgroundBrush(CreateSolidBrush(RGB(255, 255, 255))),
	handle(0)
{
	backgroundColor = GetCardColor((*cardInHandState).card);
}

CardInHandWindow::~CardInHandWindow() 
{
}

wchar_t* CardInHandWindow::nameClassWindow = L"ClassCardInHandWindow";
wchar_t* CardInHandWindow::nameWindow = L"CardInHandWindow";

bool CardInHandWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = 0;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	tag.hCursor = ::LoadCursor(NULL, IDC_ARROW);
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

bool CardInHandWindow::Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow, int id) {
	cmdShow = nCmdShow;

	handle = ::CreateWindowEx( NULL, nameClassWindow, NULL, WS_CHILD| WS_BORDER | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        parentHandle, NULL, hInstance, this );	

	if (handle == NULL) {
		::MessageBox( handle, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	staticHandle = ::CreateWindow( L"STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_CENTER,
		0, 0, 0, 0, handle, NULL, hInstance, NULL );

	if (staticHandle == NULL) {
		::MessageBox( handle, L"Can't got static handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	LOGFONT logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	logFont.lfHeight = -GetPixelSize(5);
	_tcscpy_s(logFont.lfFaceName, L"Arial");
	HFONT hFont = CreateFontIndirect(&logFont);
	SendMessage(staticHandle, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);

	PrintCard(staticHandle, (*cardInHandState).card, false);

	return true;
}

void CardInHandWindow::Show() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		::SetWindowPos( staticHandle, NULL, 0, 0, width, height, SWP_SHOWWINDOW );
	}

	::UpdateWindow(staticHandle);

	::ShowWindow( handle, cmdShow );
	::UpdateWindow(handle);
}

HWND CardInHandWindow::GetHandle() {
	return handle;
}

HWND CardInHandWindow::GetStaticHandle() {
	return staticHandle;
}

void CardInHandWindow::OnDestroy() {
	PostQuitMessage( 0 );	
}

void CardInHandWindow::OnLButtonDown() {
	if ( (cardInHandState->playerState->GetCanMove()) && ((*cardInHandState).playerState->IsCardAvailable(cardInHandState->card)) ) {
		cardInHandState->ApplyCard();
		backgroundColor = GetCardColor(cardInHandState->card);
		PrintCard(staticHandle, cardInHandState->card, false);
	}
}

void CardInHandWindow::dropCardInHand() {
	OnRButtonDown();
}

void CardInHandWindow::OnRButtonDown() {
	if ( cardInHandState->playerState->GetCanMove() ) {
		cardInHandState->DropCard();
		backgroundColor = GetCardColor(cardInHandState->card);
		PrintCard(staticHandle, cardInHandState->card, false);
	}
}

LRESULT CardInHandWindow::OnCtlcolorstatic(WPARAM wParam) {
	DeleteObject(backgroundBrush);

	SetBkColor((HDC)wParam, backgroundColor);

	backgroundBrush = CreateSolidBrush(backgroundColor);

	return (LRESULT)backgroundBrush;
}

LRESULT __stdcall CardInHandWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		CardInHandWindow* that = reinterpret_cast< CardInHandWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return DefWindowProc( handle, message, wParam, lParam );
	} 

	CardInHandWindow* that = reinterpret_cast< CardInHandWindow* >( GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;
		case WM_LBUTTONDOWN:
            that->OnLButtonDown();
			return 0;
		case WM_RBUTTONDOWN:
            that->OnRButtonDown();
			return 0;
		case WM_CTLCOLORSTATIC:
			return that->OnCtlcolorstatic(wParam);	
		default:
			return DefWindowProc( handle, message, wParam, lParam );
	}	
}