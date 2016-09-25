#pragma once

#include "Controllers/XLPlayerController.h"

class XLControllerCan
{
public:

	static bool Move(AXLPlayerController* Controller);
	static bool Strafe(AXLPlayerController* Controller);

	static bool Turn(AXLPlayerController* Controller);

	static bool Jump(AXLPlayerController* Controller);

	static bool Dodge(AXLPlayerController* Controller);

	static bool StartSprint(AXLPlayerController* Controller);
	static bool StopSprint(AXLPlayerController* Controller);

	static bool StartAttack(AXLPlayerController* Controller);
	static bool StopAttack(AXLPlayerController* Controller);

	static bool Reload(AXLPlayerController* Controller);

	static bool Melee(AXLPlayerController* Controller);

	static bool StartSpecial(AXLPlayerController* Controller);
	static bool StopSpecial(AXLPlayerController* Controller);

	static bool StartPrimaryAbility(AXLPlayerController* Controller);
	static bool StopPrimaryAbility(AXLPlayerController* Controller);

	static bool StartSecondaryAbility(AXLPlayerController* Controller);
	static bool StopSecondaryAbility(AXLPlayerController* Controller);

	static bool StartUltimate(AXLPlayerController* Controller);
	static bool StopUltimate(AXLPlayerController* Controller);

};
