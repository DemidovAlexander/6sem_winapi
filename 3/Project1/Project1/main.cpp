/*
 *автор: Демидов Александр
 *учебное заведение: МФТИ(ГУ) ФИВТ 296
 *направление: Прикладная Математика и Информатика
 *
 *WinApi Второе задание
 *
 */

#include <windows.h>
#include "overlappedWindow.h"

int _stdcall wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR commandLine, int nCmdShow ) {
	if ( !COverlappedWindow::RegisterClass(hInstance) ) {
		return 1;
	}

	if ( !CEllipseWindow::RegisterClass(hInstance) ) {
		return 1;
	}

	COverlappedWindow myWin;
	
	if ( !myWin.Create(hInstance) ) {
		return 1;
	}

	myWin.Show(nCmdShow);

	MSG message;
	BOOL getMessageResult = 0;
	while( ( getMessageResult = GetMessage( &message, NULL, 0, 0 ) ) != 0 ) {
		if ( getMessageResult == -1 ) {
			return -1;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}