#include <windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "overlappedWindow.h"
#include "resource.h"
#include <string>

BOOL __stdcall dialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

int getPixelSize(int fontSize) {
	HDC dc = GetDC(NULL);
	int pexelsy = ::GetDeviceCaps(dc, LOGPIXELSY);
	DeleteDC(dc);
	return MulDiv(fontSize, pexelsy, 72);
}

COverlappedWindow::COverlappedWindow() :
	handle(0), wasChanged(false), backgroundBrush(CreateSolidBrush(RGB(255, 255, 255)))
{
}

COverlappedWindow::~COverlappedWindow() {
	FreeLibrary(hinstLib);
	DeleteObject(backgroundBrush);
}

wchar_t* COverlappedWindow::nameClassWindow = L"ClassOverlappedWindow";
UINT MAX_BUFFER_SIZE = 255;

bool COverlappedWindow::RegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX tag;
	tag.cbSize = sizeof(WNDCLASSEX);
	tag.style = 0;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hIcon = (HICON)::LoadImage( hInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 32, 32, LR_SHARED );
	tag.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	tag.hbrBackground =  (HBRUSH)::GetStockObject(WHITE_BRUSH);
	tag.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	tag.lpszClassName = nameClassWindow;
	tag.hInstance = hInstance;
	tag.hIconSm = (HICON)::LoadImage( hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, LR_SHARED );

	if ( !::RegisterClassEx(&tag) ) {
		::MessageBox( NULL, L"Can't register class", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	return true;
}

void COverlappedWindow::CreateDialogWindow(int cmdShow) {
	dialogHandle = ::CreateDialog(::GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), handle, dialogProc);

	if (dialogHandle == NULL) {
		::MessageBox(handle, L"CreateDialog returned NULL", L"Warning!", MB_OK | MB_ICONINFORMATION);
	}

	HWND hTransparency = ::GetDlgItem(dialogHandle, IDC_SLIDER1);
	HWND hFontSize = ::GetDlgItem(dialogHandle, IDC_SLIDER2);

	::SendMessage(hTransparency, TBM_SETRANGE, FALSE, MAKELPARAM(0, 255));
	::SendMessage(hTransparency, TBM_SETPOS, TRUE, settings.getTransparency());
	::SendMessage(hFontSize, TBM_SETRANGE, FALSE, MAKELPARAM(8, 72));
	::SendMessage(hFontSize, TBM_SETPOS, TRUE, settings.getFontSize());

	DeleteObject(hTransparency);
	DeleteObject(hFontSize);

	::ShowWindow(dialogHandle, cmdShow);
}

bool COverlappedWindow::Create(HINSTANCE hInstance, int nCmdShow) {
	cmdShow = nCmdShow;

	handle = ::CreateWindowEx( WS_EX_LAYERED, nameClassWindow, NULL, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, this );	

	LPTSTR buffer = new TCHAR[MAX_BUFFER_SIZE];
	::LoadString( hInstance, IDS_STRING115, buffer, MAX_BUFFER_SIZE );
	::SetWindowText( handle, buffer );
	delete buffer;

	if (handle == NULL) {
		::MessageBox( handle, L"Can't got handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	editControlHandle = ::CreateWindow( L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | 
		ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0, 
		handle, NULL, hInstance, NULL );     

	if (editControlHandle == NULL) {
		::MessageBox( handle, L"Can't got editControlHandle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	LOGFONT logFont;
	::ZeroMemory(&logFont, sizeof(logFont));
	logFont.lfHeight = -getPixelSize(settings.getFontSize());
	_tcscpy_s(logFont.lfFaceName, L"Arial");
	HFONT hFont = CreateFontIndirect(&logFont);
	SendMessage(editControlHandle, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	DeleteObject(hFont);

	SetLayeredWindowAttributes(handle, RGB(0, 0, 0), settings.getTransparency(), LWA_ALPHA);

	HRSRC resource = ::FindResource( hInstance, MAKEINTRESOURCE(IDR_INITIALMESSAGE1), L"INITIALMESSAGE" );
	HGLOBAL resourceHandle = ::LoadResource( hInstance, resource );
	wchar_t* text = ( wchar_t * )::LockResource( resourceHandle );
	::SetWindowText( editControlHandle, (LPCWSTR)text );

	hinstLib = LoadLibrary(TEXT("WordsCountDLL.dll"));
	WordsCount = (MYPROC)GetProcAddress(hinstLib, "WordsCount");

	return true;	
}

HWND COverlappedWindow::GetHandle() {
	return handle;
}

HWND COverlappedWindow::GetEditControlHandle() {
	return editControlHandle;
}

HWND COverlappedWindow::GetDialogHandle() {
	return dialogHandle;
}

void COverlappedWindow::Show() {
	::UpdateWindow(editControlHandle);
	::ShowWindow( handle, cmdShow );
	::UpdateWindow(handle);
}

void COverlappedWindow::OnDestroy() {
	::PostQuitMessage( 0 );	
}

bool COverlappedWindow::Save() {
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
		return true;
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
		::MessageBox( handle, L"Can't write file", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		delete [] buffer; 
		return true;
	}
				
	delete [] buffer; 
	if ( !::CloseHandle(fileHandle) ) {
		::MessageBox( handle, L"Can't close file handle", L"ERROR!", MB_OK | MB_ICONEXCLAMATION );
		return true;
	}

	wasChanged = false;
	return false;
}

void COverlappedWindow::OnSize() {
	RECT rect;
	if (::GetClientRect(handle, &rect)) {
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		::SetWindowPos( editControlHandle, NULL, 0, 0, width, height, SWP_SHOWWINDOW );
	}
}

void COverlappedWindow::OnClose() {
	if (wasChanged) {
		int msgboxID = ::MessageBox( handle, (LPCWSTR)L"Сохранить изменения?", (LPCWSTR)L"Сохранение",
			MB_YESNOCANCEL | MB_ICONWARNING );

		switch (msgboxID) {
			case IDYES:
				if (Save()) {
					return;
				}
				break;
			case IDCANCEL:
				return;
		}
	}
	DestroyWindow(handle);
}

void COverlappedWindow::OnCountWords() {
	LRESULT length = ::SendMessage( editControlHandle, WM_GETTEXTLENGTH, 0, 0 );
	TCHAR *buffer = new TCHAR[length + 1];
	::SendMessage( editControlHandle, WM_GETTEXT, (WPARAM)length + 1, (LPARAM)buffer );

	::MessageBox(NULL, std::to_wstring((WordsCount)(buffer)).c_str(), L"Words count ", MB_OK);
}

void COverlappedWindow::OnCommand(WPARAM wParam) {
	switch (HIWORD(wParam)) { 
		case EN_CHANGE: 
			wasChanged = true;
			break;
		case 0:
			switch (LOWORD(wParam)) { 
			case ID_FILE_SAVE: 
				Save();
				break;
			case ID_FILE_EXIT:
				::SendMessage( handle, WM_CLOSE, NULL, NULL );
				break;
			case ID_FILE_SETTINGS:
				CreateDialogWindow(cmdShow);
				break;
			case ID_FILE_COUNTWORDS:
				OnCountWords();
				break;
			}
		case 1:
			switch (LOWORD(wParam)) { 
			case ID_ACCELERATOR1: 
				DestroyWindow(handle);
				break;
			}
	}
}

LRESULT COverlappedWindow::OnCtlcoloredit(WPARAM wParam) {
	DeleteObject(backgroundBrush);

	COLORREF fontColor;
	COLORREF backgroundColor;
		
	if (settings.isPreviewEnabled()) {
		fontColor = settings.getFontColor();
		backgroundColor = settings.getBackgroundColor();
	} else {
		fontColor = settings.getOldFontColor();
		backgroundColor = settings.getOldBackgroundColor();
	}

	SetTextColor((HDC)wParam, fontColor);
	SetBkColor((HDC)wParam, backgroundColor);

	backgroundBrush = CreateSolidBrush(backgroundColor);

	return (LRESULT)backgroundBrush;
}

void COverlappedWindow::ApplySettings() {
	int transparency;
	int fontSize;
	
	if (settings.isPreviewEnabled()) {
		transparency = settings.getTransparency();
		fontSize = settings.getFontSize();
	} else {
		transparency = settings.getOldTransparency();
		fontSize = settings.getOldFontSize();
	}

	SetLayeredWindowAttributes(handle, RGB(0, 0, 0), transparency, LWA_ALPHA);

	LOGFONT logFont;
	HFONT hFont = reinterpret_cast<HFONT>(::SendMessage( editControlHandle, WM_GETFONT, 0, 0 ));
	if (hFont == NULL) {
		hFont = reinterpret_cast<HFONT>(::GetStockObject( DEFAULT_GUI_FONT ));
	}
	::GetObject(hFont, sizeof(LOGFONT), &logFont);
	logFont.lfHeight = -getPixelSize(fontSize);
	DeleteObject(hFont);
	hFont = CreateFontIndirect(&logFont);
	SendMessage(editControlHandle, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	DeleteObject(hFont);
}

BOOL __stdcall dialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	COverlappedWindow* that = reinterpret_cast< COverlappedWindow* >(GetWindowLong(GetParent(hwndDlg), GWL_USERDATA));

	switch (message) {
		case WM_HSCROLL:
		{
			HWND hTransparency = GetDlgItem(hwndDlg, IDC_SLIDER1);
			HWND hFontSize = GetDlgItem(hwndDlg, IDC_SLIDER2);

			that->settings.setTransparency(SendMessage(hTransparency, TBM_GETPOS, 0, 0));
			that->settings.setFontSize(SendMessage(hFontSize, TBM_GETPOS, 0, 0));
		
			that->ApplySettings();

			DeleteObject(hTransparency);
			DeleteObject(hFontSize);
			return FALSE;
		}
		case WM_CLOSE:
			DestroyWindow(hwndDlg);
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					that->settings.enablePreview();
					that->settings.applyEdits();
					that->ApplySettings();
					that->settings.disablePreview();
					DestroyWindow(hwndDlg);
					return TRUE;
				case IDCANCEL:
					that->settings.enablePreview();
					that->settings.restoreEdits();
					that->ApplySettings();
					that->settings.disablePreview();
					DestroyWindow(hwndDlg);
					return TRUE;
				case IDC_CHECK1:
				{
					HWND hwndCheck = GetDlgItem(hwndDlg, IDC_CHECK1);

					LRESULT res = SendMessage(hwndCheck, BM_GETCHECK, 0, 0);
					if (res == BST_CHECKED) {
						that->settings.enablePreview();
					}

					if (res == BST_UNCHECKED) {
						that->settings.disablePreview();
					}

					that->ApplySettings();

					DeleteObject(hwndCheck);
					return FALSE;
				}
				case IDC_BUTTON1:
					that->settings.setHwndDlg(hwndDlg);

					if (that->settings.chooseFontColor()) {
						that->ApplySettings();
					}

					return FALSE;

				case IDC_BUTTON2:
					that->settings.setHwndDlg(hwndDlg);

					if (that->settings.chooseBackgroundColor()) {
						that->ApplySettings();
					}

					return FALSE;
			}
	}

	return FALSE;
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
		case WM_CTLCOLOREDIT:
			return that->OnCtlcoloredit(wParam);			
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}