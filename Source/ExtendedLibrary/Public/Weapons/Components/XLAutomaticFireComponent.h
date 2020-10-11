#pragma once

#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Cans/XLRangedWeaponCan.h"
#include "Projectiles/XLProjectile.h"
#include "XLAutomaticFireComponent.generated.h"

class UXLAmmoComponent;
class UXLAimingComponent;
class USoundCue;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLAutomaticFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLAutomaticFireComponent();

public:

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditDefaultsOnly, Category = "XL | Weapon")
	USoundCue* FireSound;

	/** out of ammo sound */
	UPROPERTY(EditDefaultsOnly, Category = "XL | Weapon")
	USoundCue* OutOfAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = "XL | Weapon")
	FName MuzzleFXPoint = "Muzzle";

	UPROPERTY(EditDefaultsOnly, Category = "XL | Weapon")
	UParticleSystem* MuzzleFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	/** firing audio (bLoopedFireSound set) */
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

public:

	void DetermineAction() override;

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

	FVector GetAdjustedAim();
	FVector GetAimDestination();
	FVector GetAimOrigin();
	FVector Trace(FVector Origin, FVector Target);

protected:
	void StartAttack();
	void FireWeapon();
	void Fire();
	void StopAttack();
};
