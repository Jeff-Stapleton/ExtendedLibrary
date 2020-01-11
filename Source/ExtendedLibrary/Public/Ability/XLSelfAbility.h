#pragma once

#include "XLAbility.h"
#include "XLSelfAbility.generated.h"

UCLASS()
class AXLSelfAbility : public AXLAbility
{
	GENERATED_BODY()
	
	void Activate();

	void Deactivate();

	void ApplyCombatEffects();	
};
