#ifndef ESP_H
#define ESP_H

#include <windows.h>
#include <windowsx.h>
#include "Drawer.h"
#include "CS.h"
namespace ESP {

	void Render(CS::LocalPlayer& LocalPlayer, CS::EntityList &EntityList);
	bool WorldToScreen(float ViewMatrix[4][4], float *Position, float w2s[2]);
	bool WorldToScreenOpenGL(float ViewMatrix[4][4], float *Position, float *flOut);
	float GetDistance(float *srcPosition, float *targetPosition);
}


#endif