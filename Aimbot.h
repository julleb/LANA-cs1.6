#ifndef AIMBOT_H
#define AIMBOT_H

#include "CS.h"
#include "Windows.h"
#include <cmath>
#include "WeaponBase.h"
namespace Aimbot {


	float GetFOV(float *localPosition, float *target, float *currentAngle);
	void aim(CS::LocalPlayer &LocalPlayer, CS::EntityList &EntityList);
}


#endif