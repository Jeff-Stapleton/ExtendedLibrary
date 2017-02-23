#pragma once

#include "Pickups/XLPickup.h"
#include "Characters/XLCharacter.h"

class XLPickupCan
{
public:
	static bool BePickedUp(AXLPickup* Pickup, AXLCharacter* Character);
};
