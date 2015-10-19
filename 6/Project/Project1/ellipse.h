#include <windows.h>

class ÑEllipse {
public:
	ÑEllipse( int, int, int, int, int );
	
	void drawEllipse(HDC dc, HWND handle);
	void moveEllipse();
	void setRect(RECT rect);

private:
	int centerx, centery, speedx, speedy;
	int radius;
	RECT border;
};