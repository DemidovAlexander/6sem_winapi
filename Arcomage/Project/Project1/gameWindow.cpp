#include <windows.h>
#include <Commctrl.h>
#include <iostream>
#include <time.h>

#include "resource.h"
#include "gameWindow.h"
#include "playerHandState.h"
#include "AIPlayer.h"

#include "utils.h"

BOOL __stdcall dialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

GameWindow::GameWindow() :
	handle(0),
	playerState(false),
	autoPlayerState(true),
	playerWindow(playerState, settings),
	autoPlayerWindow(autoPlayerState, settings),
	cardsDeckState(25),
	playerHandState(cardsDeckState, playerState, autoPlayerState),
	autoPlayerHandState(cardsDeckState, autoPlayerState, playerState),
	playerInterfaceWindow(playerHandState),
	autoPlayer(autoPlayerHandState, autoPlayerState, playerState, settings),
	gameIsEnded(false),
	isEnemyTurn(false)
{
}

GameWindow::~GameWindow()
{
}

const wchar_t* GameWindow::nameClassWindow = L"ClassGameWindow";
const wchar_t* GameWindow::nameWindow = L"GameWindow";

bool GameWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = 0;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hIcon = (HICON)::LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_SHARED);
	tag.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	tag.hbrBackground =  (HBRUSH)::GetStockObject(WHITE_BRUSH);
	tag.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	tag.lpszClassName = nameClassWindow;
	tag.hInstance = hInstance;
	tag.hIconSm = (HICON)::LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, LR_SHARED);

	if ( !::RegisterClassEx(&tag) ) {
		::MessageBox( NULL, L"Can't register class", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;
}

void GameWindow::CreateDialogWindow(int cmdShow) {
	dialogHandle = ::CreateDialog(::GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), handle, dialogProc);

	if (dialogHandle == NULL) {
		::MessageBox(handle, L"CreateDialog returned NULL", L"Warning!", MB_OK | MB_ICONINFORMATION);
	}

	HWND freezeTimeSlider = ::GetDlgItem(dialogHandle, IDC_SLIDER6);
	::SendMessage(freezeTimeSlider, TBM_SETRANGE, FALSE, MAKELPARAM(0, 5));
	::SendMessage(freezeTimeSlider, TBM_SETPOS, TRUE, 2);

	HWND roundTimeSlider = ::GetDlgItem(dialogHandle, IDC_SLIDER5);
	::SendMessage(roundTimeSlider, TBM_SETRANGE, FALSE, MAKELPARAM(0, 6));
	::SendMessage(roundTimeSlider, TBM_SETPOS, TRUE, 3);

	HWND towerVictoryHeightSlider = ::GetDlgItem(dialogHandle, IDC_SLIDER2);
	::SendMessage(towerVictoryHeightSlider, TBM_SETRANGE, FALSE, MAKELPARAM(0, 150));
	::SendMessage(towerVictoryHeightSlider, TBM_SETPOS, TRUE, 100);

	HWND metalVictoryAmountSlider = ::GetDlgItem(dialogHandle, IDC_SLIDER3);
	::SendMessage(metalVictoryAmountSlider, TBM_SETRANGE, FALSE, MAKELPARAM(0, 200));
	::SendMessage(metalVictoryAmountSlider, TBM_SETPOS, TRUE, 125);

	HWND stoneVictoryAmountSlider = ::GetDlgItem(dialogHandle, IDC_SLIDER4);
	::SendMessage(stoneVictoryAmountSlider, TBM_SETRANGE, FALSE, MAKELPARAM(0, 200));
	::SendMessage(stoneVictoryAmountSlider, TBM_SETPOS, TRUE, 125);


	settings.SetFreezeTime(::SendMessage(freezeTimeSlider, TBM_GETPOS, 0, 0));
	settings.SetRoundTime(::SendMessage(roundTimeSlider, TBM_GETPOS, 0, 0));

	settings.SetTowerVictoryHeight(::SendMessage(towerVictoryHeightSlider, TBM_GETPOS, 0, 0));
	settings.SetMetalVictoryAmount(::SendMessage(metalVictoryAmountSlider, TBM_GETPOS, 0, 0));
	settings.SetStoneVictoryAmount(::SendMessage(stoneVictoryAmountSlider, TBM_GETPOS, 0, 0));

	::DeleteObject(freezeTimeSlider);
	::DeleteObject(roundTimeSlider);
	::DeleteObject(towerVictoryHeightSlider);
	::DeleteObject(metalVictoryAmountSlider);
	::DeleteObject(stoneVictoryAmountSlider);

	::ShowWindow(dialogHandle, cmdShow);
}

bool GameWindow::Create(HINSTANCE hInstance, int nCmdShow) {
	cmdShow = nCmdShow;

	handle = ::CreateWindowEx( NULL, nameClassWindow, NULL,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_CLIPCHILDREN,
        200, 20, 1000, 700,
        NULL, NULL, hInstance, this );	

	if (handle == NULL) {
		::MessageBox( handle, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	playerWindow.Create( hInstance, handle, cmdShow );
	autoPlayerWindow.Create( hInstance, handle, cmdShow );
	logWindow.Create( hInstance, handle, cmdShow );
	playerInterfaceWindow.Create( hInstance, handle, cmdShow );
	

	CreateDialogWindow(nCmdShow);

	return true;	
}

void GameWindow::Show() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		::SetWindowPos( playerWindow.GetHandle(), NULL, 0, 0, width / 3 - 1, 2 * height / 3, 0 );
		::SetWindowPos( logWindow.GetHandle(), NULL, width / 3, 0, width / 3, 2 * height / 3, 0 );
		::SetWindowPos( autoPlayerWindow.GetHandle(), NULL, 2 * width / 3 + 1, 0, width / 3 - 1, 2 * height / 3, 0 );
		::SetWindowPos( playerInterfaceWindow.GetHandle(), NULL, 0, 2 * height / 3 + 1, width, height / 3, 0 );
	}

	::UpdateWindow(handle);
	
	playerWindow.Show();
	autoPlayerWindow.Show();

	logWindow.Show();
	playerInterfaceWindow.Show();

	::ShowWindow( handle, cmdShow );
}

HWND GameWindow::GetHandle() const {
	return handle;
}

HWND GameWindow::GetDialogHandle() const {
	return dialogHandle;
}

void GameWindow::SetRemainingTime(int _remainingTime) {
	remainingTime = _remainingTime;
}

void GameWindow::SetTimerID(UINT _timerID) {
	timerID = _timerID;
}

UINT GameWindow::GetTimerID() const {
	return timerID;
}

void GameWindow::OnDestroy() {
	::KillTimer( handle, timerID );
	::PostQuitMessage(0);
}

void GameWindow::OnTimer() {
	if (isEnemyTurn) {
		EnemyMove();
		return;
	}

	if ( !gameIsEnded) {
		--remainingTime;

		if (remainingTime < 0) {
			logWindow.PrintTimeIsOutMessage();
			::Sleep(1000);
			playerInterfaceWindow.DropCardInHand(rand() % 5);
			YourMove();
		} else {
			logWindow.PrintChooseCardMessage(remainingTime);

			if (!playerState.GetCanMove()) {
				YourMove();
			}
		}
	}
}

void GameWindow::OnClose() {
	int msgboxID = ::MessageBox( handle, (LPCWSTR)L"Do you surely want to escape?", (LPCWSTR)L"Exit",
		MB_YESNO | MB_ICONWARNING );

	switch (msgboxID) {
		case IDNO:
			return;
	}

	::DestroyWindow(dialogHandle);
	::DestroyWindow(handle);
}

void GameWindow::OnCommand(WPARAM wParam) {
	switch (HIWORD(wParam)) { 
		case 0:
			switch (LOWORD(wParam)) {
			case ID_MENU_RESTART:
				::PostMessage( NULL, WM_USER, NULL, NULL );
				break;
			case ID_MENU_EXIT:
				::SendMessage( handle, WM_CLOSE, NULL, NULL );
				break;
			}
		case 1:
			switch (LOWORD(wParam)) { 
			case ID_ACCELERATOR1: 
				::DestroyWindow(handle);
				break;
			}
	}
}

BOOL __stdcall dialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	GameWindow* that = reinterpret_cast< GameWindow* >(::GetWindowLong(::GetParent(hwndDlg), GWL_USERDATA));

	switch (message) {
		case WM_HSCROLL:
		{
			HWND freezeTimeSlider = ::GetDlgItem(hwndDlg, IDC_SLIDER6);
			HWND roundTimeSlider = ::GetDlgItem(hwndDlg, IDC_SLIDER5);
			HWND towerVictoryHeightSlider = ::GetDlgItem(hwndDlg, IDC_SLIDER2);
			HWND metalVictoryAmountSlider = ::GetDlgItem(hwndDlg, IDC_SLIDER3);
			HWND stoneVictoryAmountSlider = ::GetDlgItem(hwndDlg, IDC_SLIDER4);


			that->settings.SetFreezeTime(::SendMessage(freezeTimeSlider, TBM_GETPOS, 0, 0));
			that->settings.SetRoundTime(::SendMessage(roundTimeSlider, TBM_GETPOS, 0, 0));

			that->settings.SetTowerVictoryHeight(::SendMessage(towerVictoryHeightSlider, TBM_GETPOS, 0, 0));
			that->settings.SetMetalVictoryAmount(::SendMessage(metalVictoryAmountSlider, TBM_GETPOS, 0, 0));
			that->settings.SetStoneVictoryAmount(::SendMessage(stoneVictoryAmountSlider, TBM_GETPOS, 0, 0));

			::DeleteObject(freezeTimeSlider);
			::DeleteObject(roundTimeSlider);
			::DeleteObject(towerVictoryHeightSlider);
			::DeleteObject(metalVictoryAmountSlider);
			::DeleteObject(stoneVictoryAmountSlider);

			that->UpdatePlayersWindows();

			return FALSE;
		}
		case WM_CLOSE:
			::SendMessage(that->GetHandle(), WM_CLOSE, NULL, NULL);
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					that->SetTimerID(::SetTimer( that->GetHandle(), 0, 1000, NULL ));
					if (that->GetTimerID() == 0) {
						::MessageBox( NULL, L"Can't Set Timer", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
					}

					that->SetRemainingTime(that->settings.GetRoundTime() * 10);

					::DestroyWindow(hwndDlg);
					return TRUE;
				case IDCANCEL:
					::SendMessage(that->GetHandle(), WM_CLOSE, NULL, NULL);
					return TRUE;
			}
	}

	return FALSE;
}

void GameWindow::OnVictory() {
	gameIsEnded = true;
	logWindow.PrintVictoryText();
}

void GameWindow::OnLoss() {
	gameIsEnded = true;
	logWindow.PrintLossText();
}

bool GameWindow::CheckGameEnd() {
	if ((playerState.GetTowerHeight() >= settings.GetTowerVictoryHeight()) ||
		((playerState.GetMetalAmount() >= settings.GetMetalVictoryAmount()) && 
		(playerState.GetStoneAmount() >= settings.GetStoneVictoryAmount())) ||
		(autoPlayerState.GetTowerHeight() <= 0))
	{
		OnVictory();
		return true;
	}

	if ((autoPlayerState.GetTowerHeight() >= settings.GetTowerVictoryHeight()) ||
		((autoPlayerState.GetMetalAmount() >= settings.GetMetalVictoryAmount()) && 
		(autoPlayerState.GetStoneAmount() >= settings.GetStoneVictoryAmount())) ||
		(playerState.GetTowerHeight() <= 0))
	{
		OnLoss();
		return true;
	}

	return false;
}

void GameWindow::AutoMove() {
	autoPlayer.Move();
}

void GameWindow::UpdatePlayersWindows() {
	playerWindow.repainted = false;
	autoPlayerWindow.repainted = false;
	::InvalidateRect(playerWindow.GetHandle(), NULL, true);
	::InvalidateRect(autoPlayerWindow.GetHandle(), NULL, true);
}

void GameWindow::EnemyMove() {
	if ( ( !CheckGameEnd() ) && (playerWindow.repainted) && (autoPlayerWindow.repainted) ) {
		logWindow.PrintEnemyMove();
		::Sleep(1000);

		AutoMove();

		logWindow.PrintCardLog(autoPlayerState.GetLastUsedCard(), autoPlayerState.GetLastCardWasDropped());
		::Sleep(settings.GetFreezeTime() * 2000);

		playerState.UpdateResources();
		autoPlayerState.UpdateResources();
		UpdatePlayersWindows();

		if ( !CheckGameEnd() ) {
			remainingTime = settings.GetRoundTime() * 10;
			playerState.SetCanMove(true);
		}

		isEnemyTurn = false;
	}
}

void GameWindow::YourMove() {
	logWindow.PrintCardLog(playerState.GetLastUsedCard(), playerState.GetLastCardWasDropped());
	::Sleep(settings.GetFreezeTime() * 2000);
	UpdatePlayersWindows();
	isEnemyTurn = true;
}

LRESULT __stdcall GameWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		GameWindow* that = reinterpret_cast< GameWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		::SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return ::DefWindowProc( handle, message, wParam, lParam );
	} 

	GameWindow* that = reinterpret_cast< GameWindow* >( ::GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;
		case WM_CLOSE:
			that->OnClose();
			return 0;
		case WM_TIMER:
			that->OnTimer();
			return 0;
		case WM_USER:
			return 0;
		case WM_COMMAND:
			that->OnCommand(wParam);
			return 0;		
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}