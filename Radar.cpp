#include "Radar.h"


# define MATH_PI 3.14159265358979323846  /* pi */

namespace Radar {
	PAINTSTRUCT ps;
	HGDIOBJ original;
	int sightSize = 15;
	float scaleSize = 2.2f;
	HDC hdc;
	HBRUSH brush = CreateSolidBrush(RGB(0, 100, 0));

	//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

	int height;
	int width;
	
	int getCenterX() {
		return width / 2;
	}
	int getCenterY() {
		return height / 2;
	}
	

	void DrawCircle(int x, int y, int radius) {
		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	}
	void setBackgroundColor(HWND hWnd) {
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
		//DeleteObject(brush);
	}

	void SetupDrawing(HWND hWnd) {
		hdc = BeginPaint(hWnd, &ps);
		original = SelectObject(hdc, GetStockObject(DC_PEN));
		RECT  rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		//set background color
		setBackgroundColor(hWnd);
	}


	void EndDrawing(HWND hWnd) {
		SelectObject(hdc, original);
		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}

	void drawRectangle() {
		//HPEN hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
		SelectObject(hdc, original);
		Rectangle(hdc, 10, 10,  60, 60);
		//DeleteObject(hpen);
		
	}

	void DrawRadar() {
		//Draw sikte
		//SetBkMode(hdc, TRANSPARENT);
		//SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));


		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, width / 2, height / 2);
		MoveToEx(hdc, width, 0, NULL);
		LineTo(hdc, width / 2, height / 2);

		//draw korset
		MoveToEx(hdc, width / 2, 0, NULL);
		LineTo(hdc, width / 2, height);
		MoveToEx(hdc, 0, height / 2, NULL);
		LineTo(hdc, width, height / 2);
	}

	void DrawEntity(int x, int y) {
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(100, 0, 0));
		DrawCircle(x, y, 5);
	}

	int* GetEntityPositionInRadar(float *src, float viewAngle, float *target) {
		float angle = viewAngle * (MATH_PI / 180);
		float radarX = (src[0] - target[0]) / sightSize;
		float radarY = (src[1] - target[1]) / sightSize;

		float positionX = radarY * cos(angle) - radarX * sin(angle);
		float positionY = radarY * sin(angle) + radarX * cos(angle);

		positionX *= scaleSize;
		positionX += getCenterX();

		positionY *= scaleSize;
		positionY += getCenterY();

		int position[2];
		position[0] = (int) positionX;
		position[1] = (int)positionY;

		if (position[0] < 0) position[0] = 0;
		if (position[0] > width) position[0] = width;
		if (position[1] < 0) position[1] = 0;
		if (position[1] > height) position[1] = height;

		return position;
	}
}



