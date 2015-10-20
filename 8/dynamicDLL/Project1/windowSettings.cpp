#include <windows.h>
#include "windowSettings.h"

WindowSettings::WindowSettings() {
	for (int i = 0; i < 16; ++i) {
		fontCustColors[i] = RGB(255, 255, 255);
		backgroundCustColors[i] = RGB(255, 255, 255);
	}

	::ZeroMemory(&fontColor, sizeof(fontColor));
	fontColor.lStructSize = sizeof(fontColor);
	fontColor.lpCustColors = (LPDWORD)fontCustColors;
	fontColor.Flags = CC_FULLOPEN | CC_RGBINIT;
			
	::ZeroMemory(&backgroundColor, sizeof(backgroundColor));
	backgroundColor.lStructSize = sizeof(backgroundColor);
	backgroundColor.lpCustColors = (LPDWORD)backgroundCustColors;
	backgroundColor.Flags = CC_FULLOPEN | CC_RGBINIT;

	SetFontSize(12);
	SetTransparency(255);
	SetFontColor(RGB(0, 0, 0));
	SetBackgroundColor(RGB(255, 255, 255));
	ApplyEdits();

	DisablePreview();
}

void WindowSettings::ApplyEdits() {
	oldFontSize = fontSize;
	oldTransparency = transparency;
	oldFontColor = fontColor.rgbResult;
	oldBackGroundColor = backgroundColor.rgbResult;
}

void WindowSettings::RestoreEdits() {
	fontSize = oldFontSize;
	transparency = oldTransparency;
	fontColor.rgbResult = oldFontColor;
	backgroundColor.rgbResult = oldBackGroundColor;
}

int WindowSettings::GetFontSize() {
	return fontSize;
}

int WindowSettings::GetTransparency() {
	return transparency;
}

int WindowSettings::GetOldTransparency() {
	return oldTransparency;
}

int WindowSettings::GetOldFontSize() {
	return oldFontSize;
}

COLORREF WindowSettings::GetFontColor() {
	return fontColor.rgbResult;
}

COLORREF WindowSettings::GetBackgroundColor() {
	return backgroundColor.rgbResult;
}

COLORREF WindowSettings::GetOldFontColor() {
	return oldFontColor;
}

COLORREF WindowSettings::GetOldBackgroundColor() {
	return oldBackGroundColor;
}

bool WindowSettings::IsPreviewEnabled() {
	return preview;
}

void WindowSettings::SetFontSize(int newFontSize) {
	fontSize = newFontSize;
}

void WindowSettings::SetTransparency(int newTransparency) {
	transparency = newTransparency;
}

void WindowSettings::SetFontColor(COLORREF newColor) {
	fontColor.rgbResult = newColor;
}

void WindowSettings::SetBackgroundColor(COLORREF newColor) {
	backgroundColor.rgbResult = newColor;
}

void WindowSettings::SetHwndDlg(HWND hwndDlg) {
	fontColor.hwndOwner = hwndDlg;
	backgroundColor.hwndOwner = hwndDlg;
}

BOOL WindowSettings::ChooseFontColor() {
	return ChooseColor(&fontColor);
}

BOOL WindowSettings::ChooseBackgroundColor() {
	return ChooseColor(&backgroundColor);
}

void WindowSettings::EnablePreview() {
	preview = true;
}

void WindowSettings::DisablePreview() {
	preview = false;
}