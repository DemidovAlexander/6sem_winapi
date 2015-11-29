#pragma once

#include <windows.h>
#include "card.h"

int GetPixelSize(int fontSize);
void PrintCard( HWND staticHandle, const Card &card, bool wasDropped );
COLORREF GetCardColor( const Card &card );