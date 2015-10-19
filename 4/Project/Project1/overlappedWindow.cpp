#include <windows.h>
#include "overlappedWindow.h"

COverlappedWindow::COverlappedWindow() :
	handle(0), wasChanged(false)
{
}

COverlappedWindow::~COverlappedWindow()
{
}

wchar_t* COverlappedWindow::nameClassWindow = L"ClassOverlappedWindow";
wchar_t* COverlappedWindow::nameWindow = L"OverlappedWindow";

bool COverlappedWindow::RegisterClass(HINSTANCE hInstance) {
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

bool COverlappedWindow::Create(HINSTANCE hInstance) {
	handle = ::CreateWindow( nameClassWindow, nameWindow, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, this );	

	if (handle == NULL) {
		::MessageBox( NULL, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	editControlHandle = ::CreateWindow( L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0, 
		handle, NULL, GetModuleHandle( 0 ), NULL );     

	if (editControlHandle == NULL) {
		::MessageBox( NULL, L"Can't got editControlHandle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;	
}

void COverlappedWindow::Show(int cmdShow) {
	::UpdateWindow(editControlHandle);
	::ShowWindow( handle, cmdShow );
	::UpdateWindow(handle);
}

void COverlappedWindow::OnDestroy() {
	::PostQuitMessage( 0 );	
}

void COverlappedWindow::OnClose() {
	if (wasChanged) {
		int msgboxID = ::MessageBox( handle, (LPCWSTR)L"Сохранить изменения?", (LPCWSTR)L"Сохранение",
			MB_YESNOCANCEL | MB_ICONWARNING );

		switch (msgboxID) {
			case IDYES:
			{
				OPENFILENAME ofn;
				char fileName[MAX_PATH] = "";
				::ZeroMemory(&ofn, sizeof(ofn));

				ofn.lStructSize = sizeof(ofn); 
				ofn.hwndOwner = handle;
				ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
				ofn.lpstrFile = (LPWSTR)fileName;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.lpstrDefExt = (LPCWSTR)L"txt";

				if ( !::GetSaveFileName(&ofn) ) {
					::MessageBox( NULL, L"Can't get file name", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
					return;
				}

				LRESULT length = ::SendMessage( editControlHandle, WM_GETTEXTLENGTH, 0, 0 );
				TCHAR *buffer = new TCHAR[length + 1];
				::SendMessage( editControlHandle, WM_GETTEXT, (WPARAM)length + 1, (LPARAM)buffer );
                            
				DWORD bytesWritten = 0;
				HANDLE fileHandle = ::CreateFile( ofn.lpstrFile, GENERIC_WRITE,
					FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				
				short bom = 0xFEFF;
				if ( !::WriteFile( fileHandle, &bom, 2, &bytesWritten, NULL ) || 
					!::WriteFile( fileHandle, buffer, length * sizeof( wchar_t ), &bytesWritten, NULL )  ) {
						::MessageBox( NULL, L"Can't write file", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
						return;
				}
				
				delete [] buffer; 
				if ( !::CloseHandle(fileHandle) ) {
					::MessageBox( NULL, L"Can't close file handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
				}

				break;
			}
			case IDCANCEL:
				return;
		}
	}
	DestroyWindow(handle);
}

void COverlappedWindow::OnCommand(WPARAM wParam) {
	switch (HIWORD(wParam)) { 
		case EN_CHANGE: 
			wasChanged = true;
			break;
	}
}

void COverlappedWindow::OnSize() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		::SetWindowPos( editControlHandle, NULL, 0, 0, width, height, SWP_SHOWWINDOW );
	}
}

LRESULT __stdcall COverlappedWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam ) {
	if (message == WM_NCCREATE) { 
		COverlappedWindow* that = reinterpret_cast< COverlappedWindow* >( reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams ); 
		::SetWindowLong( handle, GWL_USERDATA, reinterpret_cast<LONG>(that) );  

		return ::DefWindowProc( handle, message, wParam, lParam ); 
	} 

	COverlappedWindow* that = reinterpret_cast< COverlappedWindow* >( ::GetWindowLong( handle, GWL_USERDATA) );

	switch( message ) {
		case WM_DESTROY:
			that->OnDestroy();
			return 0;
		case WM_CLOSE:
			that->OnClose();
			return 0;
		case WM_SIZE:
			that->OnSize();
			return 0;
		case WM_COMMAND:
			that->OnCommand(wParam);
			return 0;
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}