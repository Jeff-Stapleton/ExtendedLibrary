#pragma once

#include "XLWeapon.h"

class XLWeaponCan
{
public:
	static bool Attack(AXLWeapon* Weapon);
	static bool Reload(AXLWeapon* Weapon);
	static bool Melee(AXLWeapon* Weapon);
};
