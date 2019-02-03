#include "WeaponBase.h"

#include <iostream>
namespace CombatWeapon {

	bool isKnife(const char* weaponText) {
		std::string weaponString(weaponText);
		return (weaponString.find("knife") != std::string::npos);
		
	}

	bool isAwp(const char* weaponString) {
		return true;
	}

	bool isGrenade(const char* weaponString) {
		return true;
	}

	bool isKnife(int weaponId) {
		return weaponId == 29;
	}
	bool isGrenade(int weaponId) {
		return weaponId == 4 || weaponId == 25 || weaponId == 9;
	}
	bool isBomb(int weaponId) {
		return weaponId == 6;
	}

	bool isNonShootableWeapon(int weaponId) {
		return isKnife(weaponId) || isGrenade(weaponId) || isBomb(weaponId);
	}
}