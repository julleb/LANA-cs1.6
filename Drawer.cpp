#include "Drawer.h"

namespace Drawer {
	PAINTSTRUCT ps;
	HDC hdc;
	int width;
	int height;

	HBRUSH transparentBrush = CreateSolidBrush(RGB(0, 0, 0));

	HDC GetHDC() {
		return hdc;
	}
	int GetHeight() {
		return height;
	}
	int GetWidth() {
		return width;
	}

	void setBackgroundColor(HWND hWnd) {
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)transparentBrush);
	}
	void EndDrawing(HWND hWnd) {
		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}
	void SetupDrawing(HWND hWnd) {
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, GetStockObject(DC_PEN));
		RECT  rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		//set background color
		setBackgroundColor(hWnd);
	}

	void DrawRectangle(HPEN penColor, int x, int y, int width, int height) {
		SelectObject(hdc, penColor);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, x, y, x + width, y + height);
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	}

	void DrawFilledRectangle(HBRUSH brush, int x, int y, int width, int height) {
		SelectObject(hdc, brush);
		Rectangle(hdc, x, y, x + width, y + height);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	}

	void DrawCircle(int x, int y, int radius) {
		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	}

	void DrawText(LPCWSTR text, int x, int y) {
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 255, 0));
		RECT rect;
		rect.left = x;
		rect.top = y;
		DrawText(hdc, text, -1, &rect, DT_SINGLELINE);
	}
}