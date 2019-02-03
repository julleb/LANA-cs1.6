#ifndef DRAWER_H
#define DRAWER_H

#include <windows.h>
#include <windowsx.h>

namespace Drawer {
	int GetHeight();
	int GetWidth();
	void EndDrawing(HWND hWnd);
	void SetupDrawing(HWND hWnd);
	void DrawCircle(int x, int y, int radius);
	void DrawRectangle(HPEN hpen, int x, int y, int width, int height);
	void DrawFilledRectangle(HBRUSH brush, int x, int y, int width, int height);
	void DrawText(LPCWSTR text, int x, int y);
}

#endif