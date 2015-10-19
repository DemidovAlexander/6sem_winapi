#pragma once

#include <windows.h>

class WindowSettings {
public:
	WindowSettings();

	void applyEdits();

	void restoreEdits();

	int getFontSize();

	int getTransparency();

	int getOldTransparency();

	int getOldFontSize();

	COLORREF getFontColor();

	COLORREF getBackgroundColor();

	COLORREF getOldFontColor();

	COLORREF getOldBackgroundColor();

	bool isPreviewEnabled();

	void setFontSize(int newFontSize);

	void setTransparency(int newTransparency);

	void setFontColor(COLORREF newColor);

	void setBackgroundColor(COLORREF newColor);

	void setHwndDlg(HWND hwndDlg);

	BOOL chooseFontColor();

	BOOL chooseBackgroundColor();

	void enablePreview();

	void disablePreview();

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
