#pragma once

#include <windows.h>
#include "card.h"

int GetPixelSize(int fontSize);
void PrintCard(HWND staticHandle, Card &card, bool wasDropped);
COLORREF GetCardColor(Card &card);