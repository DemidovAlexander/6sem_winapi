#include <windows.h>
#include <memory>
#include "resource.h"

#include "gameWindow.h"
#include "PlayerWindow.h"
#include "LogWindow.h"
#include "PlayerInterfaceWindow.h"
#include "CardInHandWindow.h"

bool RegisterWindows(HINSTANCE hInstance) {
	if ( !GameWindow::RegisterClass(hInstance) ) {
		return false;
	}

	if ( !PlayerWindow::RegisterClass(hInstance) ) {
		return false;
	}

	if ( !LogWindow::RegisterClass(hInstance) ) {
		return false;
	}

	if ( !PlayerInterfaceWindow::RegisterClass(hInstance) ) {
		return false;
	}
	
	if ( !CardInHandWindow::RegisterClass(hInstance) ) {
		return false;
	}

	return true;
}

int _stdcall wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR commandLine, int nCmdShow ) {
	if ( !RegisterWindows(hInstance) ) {
		return 1;
	}
	
	std::shared_ptr<GameWindow> myGameWin = std::make_shared<GameWindow>();
	
	if ( !myGameWin->Create(hInstance, nCmdShow) ) {
		return 1;
	}

	myGameWin->Show();

	HACCEL haccel = ::LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );

	MSG message;
	BOOL getMessageResult = 0;
	while( ( getMessageResult = ::GetMessage( &message, NULL, 0, 0 ) ) != 0 ) {
		if ( getMessageResult == -1 ) {
			return -1;
		}

		if 	( message.message ==  WM_USER ) {
			::SendMessage( myGameWin->GetHandle(), WM_DESTROY, NULL, NULL );

			myGameWin = std::make_shared<GameWindow>();

			if ( !myGameWin->Create(hInstance, nCmdShow) ) {
				return 1;
			}

			myGameWin->Show();
		} else {
			if( !::TranslateAccelerator( myGameWin->GetHandle(), haccel, &message ) ) {
				::TranslateMessage( &message );
				::DispatchMessage( &message );
			}
		}
	}

	::DestroyAcceleratorTable(haccel);

	return message.wParam;
}