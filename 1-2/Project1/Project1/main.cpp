/*
 *автор: Демидов Александр
 *учебное заведение: МФТИ(ГУ) ФИВТ 296
 *направление: Прикладная Математика и Информатика
 *
 *WinApi Первое задание
 *
 */

#include <windows.h>
#include "ellipseWindow.h"

int _stdcall wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR commandLine, int nCmdShow ) {
	if ( !CEllipseWindow::RegisterClass(hInstance) ) {
		return 1;
	}

	CEllipseWindow myWin;
	
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