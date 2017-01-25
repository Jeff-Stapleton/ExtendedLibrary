#pragma once

#include "Characters/XLCharacter.h"

class XLCharacterCan
{
public:
	static bool Jump(AXLCharacter* Character);

	static bool Move(AXLCharacter* Character);
	static bool Strafe(AXLCharacter* Character);

	static bool Turn(AXLCharacter* Character);
	static bool LookUp(AXLCharacter* Character);

	static bool StartSprint(AXLCharacter* Character);
	static bool StopSprint(AXLCharacter* Character);

	static bool StartAbility(AXLCharacter* Character);
	static bool StopAbility(AXLCharacter* Character);

	static bool Die(AXLCharacter* Character);
};
