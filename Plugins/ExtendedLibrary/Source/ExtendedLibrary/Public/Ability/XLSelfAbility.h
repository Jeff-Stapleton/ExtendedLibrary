#pragma once

#include "XLAbility.h"
#include "XLSelfAbility.generated.h"

UCLASS()
class UXLSelfAbility : public UXLAbility
{
	GENERATED_BODY()
	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Activate();

	void Deactivate();

	void ApplyCombatEffects();	
};
