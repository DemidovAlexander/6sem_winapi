#pragma once

#include <windows.h>
#include "playerWindow.h"
#include "logWindow.h"
#include "playerInterfaceWindow.h"
#include "playerHandState.h"
#include "cardsDeckState.h"
#include "AIPlayer.h"
#include "settings.h"

class GameWindow {
public:
	Settings settings;

    GameWindow();
    ~GameWindow();

    // Зарегистрировать класс окна
    static bool RegisterClass(HINSTANCE hInstance);

    // Создать экземпляр окна
    bool Create( HINSTANCE hInstance, int nCmdShow );

    // Показать окно
    void Show();

	HWND GetHandle() const;
	HWND GetDialogHandle() const;

	void SetRemainingTime(int _remainingTime);

	void SetTimerID(UINT _timerID);
	UINT GetTimerID() const;

	void UpdatePlayersWindows();

protected:
    void OnDestroy();
	void OnClose();
	void OnCommand(WPARAM wParam);

	void OnTimer();
	void OnVictory();
	void OnLoss();

	void YourMove();
	void EnemyMove();

	void CreateDialogWindow(int cmdShow);

	void AutoMove();
	bool CheckGameEnd();

private:
	const static wchar_t* nameClassWindow; 
	const static wchar_t* nameWindow; 

	int cmdShow;

    HWND handle;
	HWND dialogHandle;

	UINT timerID;

	PlayerState playerState;
	PlayerState autoPlayerState;
	CardsDeckState cardsDeckState;

	PlayerHandState playerHandState;
	PlayerHandState autoPlayerHandState;

	PlayerWindow playerWindow;
	PlayerWindow autoPlayerWindow;
	LogWindow logWindow;
	PlayerInterfaceWindow playerInterfaceWindow;

	AIPlayer autoPlayer;

	bool gameIsEnded;
	bool isEnemyTurn;

	int remainingTime;

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};