#pragma once

#include <windows.h>

class CEllipse {
public:
	CEllipse( int, int, int, int, int );
	
	void drawEllipse(HDC dc);
	void moveEllipse();
	void setRect(RECT rect);

private:
	int centerx, centery, speedx, speedy;
	int radius;
	RECT border;
};