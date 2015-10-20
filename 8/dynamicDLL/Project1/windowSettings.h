#pragma once

#include <windows.h>

class WindowSettings {
public:
	WindowSettings();

	void ApplyEdits();

	void RestoreEdits();

	int GetFontSize();

	int GetTransparency();

	int GetOldTransparency();

	int GetOldFontSize();

	COLORREF GetFontColor();

	COLORREF GetBackgroundColor();

	COLORREF GetOldFontColor();

	COLORREF GetOldBackgroundColor();

	bool IsPreviewEnabled();

	void SetFontSize(int newFontSize);

	void SetTransparency(int newTransparency);

	void SetFontColor(COLORREF newColor);

	void SetBackgroundColor(COLORREF newColor);

	void SetHwndDlg(HWND hwndDlg);

	BOOL ChooseFontColor();

	BOOL ChooseBackgroundColor();

	void EnablePreview();

	void DisablePreview();

private:
	int fontSize;
	int oldFontSize;

	int transparency;
	int oldTransparency;

	CHOOSECOLOR fontColor;
	CHOOSECOLOR backgroundColor;

	COLORREF oldFontColor;
	COLORREF oldBackGroundColor;

	COLORREF fontCustColors[16];
	COLORREF backgroundCustColors[16];

	bool preview;
};
