#include <windows.h>
#include "windowSettings.h"

WindowSettings::WindowSettings() {
	for (int i = 0; i < 16; ++i) {
		fontCustColors[i] = RGB(255, 255, 255);
		backgroundCustColors[i] = RGB(255, 255, 255);
	}

	ZeroMemory(&fontColor, sizeof(fontColor));
	fontColor.lStructSize = sizeof(fontColor);
	fontColor.lpCustColors = (LPDWORD)fontCustColors;
	fontColor.Flags = CC_FULLOPEN | CC_RGBINIT;
			
	ZeroMemory(&backgroundColor, sizeof(backgroundColor));
	backgroundColor.lStructSize = sizeof(backgroundColor);
	backgroundColor.lpCustColors = (LPDWORD)backgroundCustColors;
	backgroundColor.Flags = CC_FULLOPEN | CC_RGBINIT;

	setFontSize(12);
	setTransparency(255);
	setFontColor(RGB(0, 0, 0));
	setBackgroundColor(RGB(255, 255, 255));
	applyEdits();

	disablePreview();
}

void WindowSettings::applyEdits() {
	oldFontSize = fontSize;
	oldTransparency = transparency;
	oldFontColor = fontColor.rgbResult;
	oldBackGroundColor = backgroundColor.rgbResult;
}

void WindowSettings::restoreEdits() {
	fontSize = oldFontSize;
	transparency = oldTransparency;
	fontColor.rgbResult = oldFontColor;
	backgroundColor.rgbResult = oldBackGroundColor;
}

int WindowSettings::getFontSize() {
	return fontSize;
}

int WindowSettings::getTransparency() {
	return transparency;
}

int WindowSettings::getOldTransparency() {
	return oldTransparency;
}

int WindowSettings::getOldFontSize() {
	return oldFontSize;
}

COLORREF WindowSettings::getFontColor() {
	return fontColor.rgbResult;
}

COLORREF WindowSettings::getBackgroundColor() {
	return backgroundColor.rgbResult;
}

COLORREF WindowSettings::getOldFontColor() {
	return oldFontColor;
}

COLORREF WindowSettings::getOldBackgroundColor() {
	return oldBackGroundColor;
}

bool WindowSettings::isPreviewEnabled() {
	return preview;
}

void WindowSettings::setFontSize(int newFontSize) {
	fontSize = newFontSize;
}

void WindowSettings::setTransparency(int newTransparency) {
	transparency = newTransparency;
}

void WindowSettings::setFontColor(COLORREF newColor) {
	fontColor.rgbResult = newColor;
}

void WindowSettings::setBackgroundColor(COLORREF newColor) {
	backgroundColor.rgbResult = newColor;
}

void WindowSettings::setHwndDlg(HWND hwndDlg) {
	fontColor.hwndOwner = hwndDlg;
	backgroundColor.hwndOwner = hwndDlg;
}

BOOL WindowSettings::chooseFontColor() {
	return ChooseColor(&fontColor);
}

BOOL WindowSettings::chooseBackgroundColor() {
	return ChooseColor(&backgroundColor);
}

void WindowSettings::enablePreview() {
	preview = true;
}

void WindowSettings::disablePreview() {
	preview = false;
}