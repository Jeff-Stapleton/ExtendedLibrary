#pragma once

#include "XLWeaponSounds.generated.h"

class AXLRangedWeapon;
class USoundCue;

USTRUCT(BlueprintType)
struct FWeaponSounds
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* OutOfAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* ReloadSound;
};