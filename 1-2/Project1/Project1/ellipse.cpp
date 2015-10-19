#include "ellipse.h"
#include <iostream>

CEllipse::CEllipse( int cx, int cy, int spx, int spy, int r ) {
	centerx = cx;
	centery = cy;
	speedx = spx;
	speedy = spy;
	radius = r;
}

void CEllipse::setRect(RECT rect) {
	border = rect;

	if( centerx - radius <= border.left ) {
		centerx = border.left + radius;
	}

	if( centerx + radius >= border.right ) {
		centerx = border.right - radius;
	}

	if( centery - radius <= border.top ) {
		centery = border.top + radius;
	} 

	if( centery + radius >= border.bottom ) {
		centery = border.bottom - radius;
	}
}

void CEllipse::moveEllipse() {
	int newCordx = centerx + speedx;
	int newCordy = centery + speedy;
	std::swap(newCordx, centerx);
	std::swap(newCordy, centery);

	if( speedx < 0 ) {
		if( centerx - radius <= border.left ) {
			speedx = -speedx;
			centerx = border.left + radius;
		}
	} else {
		if( centerx + radius >= border.right ) {
			speedx = -speedx;
			centerx = border.right - radius;
		}
	}
	if( speedy < 0 ) {
		if( centery - radius <= border.top ) {
			speedy = -speedy;
			centery = border.top + radius;
		}
	} else {
		if( centery + radius >= border.bottom ) {
			speedy = -speedy;
			centery = border.bottom - radius;
		}
	}
}

void CEllipse::drawEllipse(HDC dc) {
	HBRUSH ellipseBrush;
	ellipseBrush = CreateSolidBrush( RGB( 0, 200, 255 ) );
	SelectObject( dc, ellipseBrush );
	Ellipse( dc, centerx - radius, centery - radius, centerx + radius, centery + radius );
	DeleteObject( ellipseBrush );
}