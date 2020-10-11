#pragma once

#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Cans/XLRangedWeaponCan.h"
#include "XLSemiautoBurstFireComponent.generated.h"

class USoundCue;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSemiautoBurstFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLSemiautoBurstFireComponent();
	void InitializeComponent() override;

public:

	/** The amount of time between each projectile in a given burst */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenBursts = 0.05f;

	/** The number of projectiles that will be fire in a given burst */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int NumberOfBursts = 3;

	/** firing audio (bLoopedFireSound set) */
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireLoopSound;

	/** out of ammo sound */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* OutOfAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	FName MuzzleFXPoint;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	UParticleSystem* MuzzleFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	uint16 BurstCounter = 0;
	FTimerHandle BurstTimer;

public:

	void DetermineAction();

protected:
	void StartAttack();
	void FireWeapon();
	void Fire();
	void StopAttack();
};
