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
	int remainingTime;
	UINT timerID;

    GameWindow();
    ~GameWindow();

    // Зарегистрировать класс окна
    static bool RegisterClass(HINSTANCE hInstance);

    // Создать экземпляр окна
    bool Create(HINSTANCE hInstance, int nCmdShow);

    // Показать окно
    void Show();

	HWND GetHandle();
	HWND GetDialogHandle();

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
	bool CheckEndGame();

private:
	static wchar_t* nameClassWindow; 
	static wchar_t* nameWindow; 

	int cmdShow;

    HWND handle;
	HWND dialogHandle;

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

    static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};