#pragma once

#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Cans/XLRangedWeaponCan.h"
#include "XLSemiautomaticFireComponent.generated.h"

class UXLAimingComponent;
class USoundCue;
class AXLProjectile;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSemiautomaticFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLSemiautomaticFireComponent();
	//void InitializeComponent() override;

public:

	/** firing audio (bLoopedFireSound set) */
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

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

	float LastAttackTime = 0.0f;
	FTimerHandle FiringTimer;

public:

	void DetermineAction();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

protected:
	void StartAttack();
	void FireWeapon();
	void StopAttack();
};
