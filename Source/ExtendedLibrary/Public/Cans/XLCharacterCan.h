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

	static bool StartCrouch(AXLCharacter* Character);
	static bool StopCrouch(AXLCharacter* Character);

	static bool StartProne(AXLCharacter* Character);
	static bool StopProne(AXLCharacter* Character);

	static bool StartSprint(AXLCharacter* Character);
	static bool StopSprint(AXLCharacter* Character);

	static bool StartEquip(AXLCharacter* Character, AXLItem* Weapon);
	static bool StopEquip(AXLCharacter* Character);

	static bool StartAim(AXLCharacter* Character);
	static bool StopAim(AXLCharacter* Character);

	static bool StartAttack(AXLCharacter* Character);
	static bool StopAttack(AXLCharacter* Character);

	static bool StartReload(AXLCharacter* Character);
	static bool StopReload(AXLCharacter* Character);

	static bool StartAbility(AXLCharacter* Character);
	static bool StopAbility(AXLCharacter* Character);

	static bool Die(AXLCharacter* Character);
};
