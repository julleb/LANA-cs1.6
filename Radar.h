#ifndef RADAR_H
#define RADAR_H

#include <windows.h>
#include <windowsx.h>
#include <math.h>

namespace Radar {
	
	void EndDrawing(HWND hWnd);
	void DrawRadar();
	void SetupDrawing(HWND hWnd);
	void DrawEntity(int x, int y);
	int* GetEntityPositionInRadar(float *src, float viewAngle, float *target);
}


#endif

