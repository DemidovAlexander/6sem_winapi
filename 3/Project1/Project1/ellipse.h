#include <windows.h>

class СEllipse {
public:
	СEllipse( int, int, int, int, int );
	
	void DrawEllipse(HDC dc, HWND handle);
	void MoveEllipse();
	void SetRect(RECT rect);

private:
	int centerx, centery, speedx, speedy;
	int radius;
	RECT border;
};