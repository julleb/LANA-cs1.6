#ifndef WEAPONBASE_H
#define WEAPONBASE_H

#include <string>

namespace CombatWeapon {

	bool isKnife(const char* weaponString);

	bool isAwp(const char* weaponString);

	bool isKnife(int weaponId);
	bool isGrenade(int weaponId);

	bool isNonShootableWeapon(int weaponId);
}

#endif