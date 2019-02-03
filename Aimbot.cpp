#include "Aimbot.h"

#include "Config.h"

namespace Aimbot {


	float Distance(float *src, float *target) {
		float x = src[0] - target[0];
		x = x*x;
		float y = src[1] - target[1];
		y = y*y;
		float z = src[2] - target[2];
		z = z*z;
		return sqrt(x + y + z);
	}

	void CalcAngle(float *src, float *dst, float *angles) {
		double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		angles[1] = (float)atanf(delta[1] / delta[0]) * 57.295779513082f;
		angles[0] = (float)atan2f(delta[2], hyp) * 57.295779513082f;
		angles[2] = 0.0f;
		if (delta[0] >= 0.0) { angles[1] += 180.0f; }
	}


	void AngleNormalize(float *angles) {

		for (int i = 0; i < 3; i++) {
			if (angles[i] < -180.0f) angles[i] += 360.0f;
			if (angles[i] >  180.0f) angles[i] -= 360.0f;
		}
	}


	void Smooth(int smooth, float *ViewAngle, float *AimAngles) {
		float diff[3];
		diff[0] = ViewAngle[0] - AimAngles[0];
		diff[1] = ViewAngle[1] - AimAngles[1];
		AngleNormalize(diff);
		AimAngles[0] = ViewAngle[0] - diff[0] / smooth;
		AimAngles[1] = ViewAngle[1] - diff[1] / smooth;

	}

	void aim(CS::LocalPlayer &LocalPlayer, CS::EntityList &EntityList) {
		if (CombatWeapon::isNonShootableWeapon(LocalPlayer.weaponId)) return;
		float angles[3];
		CalcAngle(LocalPlayer.position, EntityList.position, angles);
		Smooth(Config::config.smooth, LocalPlayer.viewAngles, angles);
		AngleNormalize(angles);
		LocalPlayer.SetAngles(angles);
	}

	void MakeVector(float *angle, float *vector) {
		float pitch = (float)(angle[0] * 3.14159265 / 180);
		float yaw = (float)(angle[1] * 3.14159265 / 180);
		float tmp = (float)cos(pitch);
		vector[0] = (float)(-tmp*-cos(yaw));
		vector[1] = (float)(sin(yaw)*tmp);
		vector[2] = (float)-sin(pitch);
	}

	float GetFOV(float *localPosition, float *target, float *currentAngle) {
		float aimAngle[3];
		CalcAngle(localPosition, target, aimAngle);

		float vec_One[3], vec_Two[3];
		MakeVector(currentAngle, vec_One);
		MakeVector(aimAngle, vec_Two);
		float mag_s = sqrt((vec_One[0] * vec_One[0]) + (vec_One[1] * vec_One[1]) + (vec_One[2] * vec_One[2]));
		float udot = vec_One[0] * vec_Two[0] + vec_One[1] * vec_Two[1] + vec_One[2] * vec_Two[2];
		return acos(udot / (mag_s*mag_s)) * (180.0 / 3.14159265);
	}


}