#pragma once

#include <windows.h>
#include "cardInHandState.h"


class CardInHandWindow {
public:
	CardInHandWindow(CardInHandState* _cardInHandState);
	~CardInHandWindow();

	// Зарегистрировать класс окна
	static bool RegisterClass(HINSTANCE hInstance);

	// Создать экземпляр окна
	bool Create(HINSTANCE hInstance, HWND parentHandle, int cmdShow, int id);

	// Показать окно
	void Show();

	HWND GetHandle();
	HWND GetStaticHandle();

	void dropCardInHand();

protected:
	void OnDestroy();

	void OnLButtonDown();
	void OnRButtonDown();

	LRESULT OnCtlcolorstatic(WPARAM wParam);

private:
	static wchar_t* nameClassWindow;
	static wchar_t* nameWindow;

	HWND handle;
	HWND staticHandle;

	int cmdShow;

	HBRUSH backgroundBrush;
	COLORREF backgroundColor;

	CardInHandState* cardInHandState;

	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
};