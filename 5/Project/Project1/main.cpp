/*
 *автор: Демидов Александр
 *учебное заведение: МФТИ(ГУ) ФИВТ 296
 *направление: Прикладная Математика и Информатика
 *
 *WinApi Третье задание
 *
 */

#include <windows.h>
#include "overlappedWindow.h"
#include "resource.h"

int _stdcall wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR commandLine, int nCmdShow ) {
	if ( !COverlappedWindow::RegisterClass(hInstance) ) {
		return 1;
	}

	COverlappedWindow myWin;
	
	if ( !myWin.Create(hInstance) ) {
		return 1;
	}

	myWin.Show(nCmdShow);

	HACCEL haccel = ::LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );

	MSG message;
	BOOL getMessageResult = 0;
	while( ( getMessageResult = ::GetMessage( &message, NULL, 0, 0 ) ) != 0 ) {
		if ( getMessageResult == -1 ) {
			return -1;
		}
		if( !::TranslateAccelerator( myWin.GetHandle(), haccel, &message ) ) {
			::TranslateMessage( &message );
			::DispatchMessage( &message );
		}
	}

	return message.wParam;
}