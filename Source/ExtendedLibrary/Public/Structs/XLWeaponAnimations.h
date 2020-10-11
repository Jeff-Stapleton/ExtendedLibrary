#pragma once

#include "XLWeaponAnimations.generated.h"

class AXLRangedWeapon;

USTRUCT(BlueprintType)
struct FWeaponAnimations
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* MeleeAnim;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* ReloadAnim;

};