#pragma once

#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Cans/XLRangedWeaponCan.h"
#include "XLChargeComponent.generated.h"

class UXLAimingComponent;
class USoundCue;
class AXLProjectile;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLChargeComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLChargeComponent();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Projectile")
	float ChargeTime = 0.0f;

	FTimerHandle ChargeTimer;

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile();

	void StartAttack();
	void FireWeapon();
	void StopAttack();
};
