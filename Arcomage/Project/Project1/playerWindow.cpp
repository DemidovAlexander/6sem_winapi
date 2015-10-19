#include <windows.h>
#include <string>

#include "playerWindow.h"
#include "playerState.h"
#include "settings.h"

PlayerWindow::PlayerWindow(PlayerState* _playerState, Settings* _settings) :
	settings(_settings),
	playerState(_playerState),
	repainted(true),
	handle(0)
{
}

PlayerWindow::~PlayerWindow() 
{
}

wchar_t* PlayerWindow::nameClassWindow = L"ClassPlayerWindow";
wchar_t* PlayerWindow::nameWindow = L"PlayerWindow";

bool PlayerWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = CS_HREDRAW | CS_VREDRAW;
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

bool PlayerWindow::Create(HINSTANCE hInstance, HWND parentHandle, int nCmdShow) {
	cmdShow = nCmdShow;

	handle = CreateWindow( nameClassWindow, nameWindow, WS_CHILD | WS_VISIBLE | WS_BORDER,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, parentHandle, NULL, hInstance, this );

    if (handle == NULL) {
		MessageBox( NULL, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;	
}

void PlayerWindow::Show() {
	ShowWindow( handle, cmdShow );
	UpdateWindow( handle );
}

HWND PlayerWindow::GetHandle() {
	return handle;
}

void PlayerWindow::OnDestroy() {
	PostQuitMessage( 0 );	
}

void PlayerWindow::OnPaint() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint( handle, &ps );
	HDC newHdc = CreateCompatibleDC(hdc);
	RECT rect;
	GetClientRect(handle, &rect);

	HBITMAP bitmap = CreateCompatibleBitmap( hdc, rect.right - rect.left, rect.bottom - rect.top );
	HGDIOBJ oldbitmap = SelectObject(newHdc, bitmap);

	drawBuildings(newHdc);
	drawStats(newHdc);

	BitBlt( hdc, 0, 0, rect.right, rect.bottom, newHdc, 0, 0, SRCCOPY );
	
	SelectObject(newHdc, oldbitmap);
	DeleteObject(bitmap);

	DeleteDC(hdc);
	DeleteDC(newHdc);

	EndPaint(handle, &ps);

	repainted = true;
}

void PlayerWindow::drawBuildings(HDC dc) {
	RECT clientRect;
	GetClientRect(handle, &clientRect);

	HBRUSH clientRectBrush = CreateSolidBrush( RGB(175, 238, 238) );
	FillRect( dc, &clientRect, clientRectBrush );
	DeleteObject(clientRectBrush);


	int towerPositionModifier = 0;
	int wallPositionModifier = 0;
	HBRUSH towerBrush = CreateSolidBrush( RGB(100, 100, 220) );

	if ((*playerState).IsAuto()) {
		towerPositionModifier = clientRect.right - clientRect.left - 30 - 80;
		wallPositionModifier = clientRect.right - clientRect.left - 100 - 120;

		DeleteObject(towerBrush);
		towerBrush = CreateSolidBrush( RGB(238, 0, 0) );
	}

	int heightElement = 320 / settings->GetTowerVictoryHeight();

	RECT tower;
	tower.left = clientRect.left + 30 + towerPositionModifier;
	tower.right = tower.left + 50;
	tower.bottom = clientRect.bottom;
	tower.top = tower.bottom - heightElement * playerState->GetTowerHeight();

	FillRect( dc, &tower, towerBrush );
	DeleteObject(towerBrush);

	RECT line;
	line.left = clientRect.left;
	line.right = clientRect.right;
	line.bottom = tower.bottom - 335;
	line.top = tower.bottom - 336;

	HBRUSH lineBrush = CreateSolidBrush( RGB(100, 100, 220) );
	FillRect( dc, &line, lineBrush );
	DeleteObject(lineBrush);

	RECT wall;
	wall.left = clientRect.left + 100 + wallPositionModifier;
	wall.right = wall.left + 20;
	wall.bottom = clientRect.bottom;
	wall.top = wall.bottom - min(heightElement * playerState->GetWallHeight(), 320);

	HBRUSH wallBrush = CreateSolidBrush( RGB(139, 90, 43) );
	FillRect( dc, &wall, wallBrush );
	DeleteObject(wallBrush);
}

void PlayerWindow::drawStats(HDC dc) {
	RECT clientRect;
	GetClientRect(handle, &clientRect);

	std::string text = "Tower ";
	text += std::to_string(playerState->GetTowerHeight());
	text += "/" + std::to_string(settings->GetTowerVictoryHeight());
	TextOut ( dc, clientRect.left + 10, clientRect.top + 40, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );

	text = "Wall ";
	text += std::to_string(playerState->GetWallHeight());
	TextOut ( dc, clientRect.left + 10, clientRect.top + 60, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );

	text = "Quarries ";
	text += std::to_string(playerState->GetQuarriesNumber());
	TextOut ( dc, clientRect.left + 120, clientRect.top + 40, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );

	text = "Mines ";
	text += std::to_string(playerState->GetMinesNumber());
	TextOut ( dc, clientRect.left + 120, clientRect.top + 60, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );	

	text = "Stone ";
	text += std::to_string(playerState->GetStoneAmount());
	text += "/" + std::to_string(settings->GetStoneVictoryAmount());
	TextOut ( dc, clientRect.left + 220, clientRect.top + 40, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );

	text = "Metal ";
	text += std::to_string(playerState->GetMetalAmount());
	text += "/" + std::to_string(settings->GetMetalVictoryAmount());
	TextOut ( dc, clientRect.left + 220, clientRect.top + 60, 
		(LPCWSTR)std::wstring(text.begin(), text.end()).c_str(), text.length() );	
}

LRESULT __stdcall PlayerWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) {
		PlayerWindow* that = reinterpret_cast< PlayerWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return DefWindowProc( handle, message, wParam, lParam ); 
	} 

	PlayerWindow* that = reinterpret_cast< PlayerWindow* >( GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;
		case WM_PAINT:
			that->OnPaint();
			return 0;
		case WM_ERASEBKGND:
			return 1;
		default:
			return DefWindowProc( handle, message, wParam, lParam );
	}	
}