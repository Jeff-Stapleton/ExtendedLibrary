#pragma once

#include "Data/XLCharacterResources.h"

class XLCharacterResourcesCan
{
public:
	static bool RegenerateHealth(UXLCharacterResources* Resources);
	static bool RegenerateEnergy(UXLCharacterResources* Resources);
	static bool RegenerateStamina(UXLCharacterResources* Resources);
	static bool RegenerateShield(UXLCharacterResources* Resources);
};
