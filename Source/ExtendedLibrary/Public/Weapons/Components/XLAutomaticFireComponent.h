#pragma once

#include "XLFireComponent.h"
#include "XLRangedWeaponCan.h"
#include "XLAutomaticFireComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLAutomaticFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLAutomaticFireComponent();
	void InitializeComponent() override;

public:
	/** The amount of time that must pass before being able to attack again */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenAttacks = 0.20f;

	/** firing audio (bLoopedFireSound set) */
	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	/** single fire sound (bLoopedFireSound not set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireSound;

	/** looped fire sound (bLoopedFireSound set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireLoopSound;

	/** finished burst sound (bLoopedFireSound set) */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireFinishSound;

	/** out of ammo sound */
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* OutOfAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	FName MuzzleFXPoint;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	UParticleSystem* MuzzleFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	float LastAttackTime = 0.0f;
	FTimerHandle FiringTimer;

public:
	UFUNCTION()
	void DetermineAction();

protected:
	void StartAttack();
	void FireWeapon();
	void Fire();
	void StopAttack();
};