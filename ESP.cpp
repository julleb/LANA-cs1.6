#include "ESP.h"
#include <iostream>
#include "Config.h"
namespace ESP {

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(200, 0, 0));

	
	void Render(CS::LocalPlayer& LocalPlayer, CS::EntityList &EntityList) {
		if (Config::config.esp == 0) return;
		float distance = GetDistance(LocalPlayer.position, EntityList.position);
		if (distance < 10) return;
		float w2s[2];
		bool ok = false;
		ok = WorldToScreenOpenGL(LocalPlayer.ViewMatrix, EntityList.position, w2s);
		if (!ok) return;

		float drawx = 13000.0f / distance;
		float drawy = 30000.0f / distance;
		Drawer::DrawRectangle(greenPen, w2s[0] - drawx / 2, w2s[1] - drawy / 2, drawx, drawy);
	}
	

	float GetDistance(float *srcPosition, float *targetPosition) {
		float fDist[3];
		fDist[0] = srcPosition[0] - targetPosition[0];
		fDist[1] = srcPosition[1] - targetPosition[1];
		fDist[2] = srcPosition[2] - targetPosition[2];
		return sqrt((fDist[0] * fDist[0] + fDist[1] * fDist[1] + fDist[2] * fDist[2]));

	}
	
	//////////////////////////////////
//convert 3d pos to 2d pos
/////////////////////////////
	bool WorldToScreen(float ViewMatrix[4][4], float *Position, float w2s[2]){
		float ww = ViewMatrix[3][0] * Position[0] + ViewMatrix[3][1] *Position[1] + ViewMatrix[3][2] * Position[2] + ViewMatrix[3][3];
		if(ww<0.01)
			return false;
		float invw = 1/ww;
		float xx = (ViewMatrix[0][0]*Position[0] + ViewMatrix[0][1]*Position[1] + ViewMatrix[0][2]*Position[2] + ViewMatrix[0][3])*invw;
		float yy = (ViewMatrix[1][0] * Position[0] + ViewMatrix[1][1] * Position[1] + ViewMatrix[1][2] * Position[2] + ViewMatrix[1][3]) * invw;
		float X = (xx + 1) * 0.5 * Drawer::GetWidth();
		float Y = (yy - 1) * -0.5 * Drawer::GetHeight();
		w2s[0] = X;
		w2s[1] = Y;
		return true;

	}

	bool WorldToScreenOpenGL(float ViewMatrix[4][4], float *Position, float *flOut)
	{
		flOut[0] = ViewMatrix[0][0] * Position[0] + ViewMatrix[1][0] * Position[1] + ViewMatrix[2][0] * Position[2] + ViewMatrix[3][0];
		flOut[1] = ViewMatrix[0][1] * Position[0] + ViewMatrix[1][1] * Position[1] + ViewMatrix[2][1] * Position[2] + ViewMatrix[3][1];
		float ww = ViewMatrix[0][3] * Position[0] + ViewMatrix[1][3] * Position[1] + ViewMatrix[2][3] * Position[2] + ViewMatrix[3][3];

		if (ww != 0.0f)
		{
			float flTmp = 1.0f / ww;
			flOut[0] *= flTmp;
			flOut[1] *= flTmp;
		}

		if (ww>0.0f)
		{
			flOut[0] = (flOut[0] + 1.0f) * 0.5 * Drawer::GetWidth();
			flOut[1] = (-flOut[1] + 1.0f) * 0.5 * Drawer::GetHeight();
			return true;
		}
		return false;
	}
}