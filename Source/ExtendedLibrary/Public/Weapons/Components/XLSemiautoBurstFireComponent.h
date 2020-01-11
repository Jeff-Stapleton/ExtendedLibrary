#pragma once

#include "XLFireComponent.h"
#include "XLRangedWeaponCan.h"
#include "XLSemiautoBurstFireComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSemiautoBurstFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLSemiautoBurstFireComponent();
	void InitializeComponent() override;

public:
	/** The amount of time that must pass before being able to attack again */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenAttacks = 0.50f;

	/** The amount of time between each projectile in a given burst */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenBursts = 0.05f;

	/** The number of projectiles that will be fire in a given burst */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	int NumberOfBursts = 3;

	float LastAttackTime = 0.0f;
	uint16 BurstCounter = 0;
	FTimerHandle FiringTimer;
	FTimerHandle BurstTimer;

public:
	UFUNCTION()
	void DetermineAction();

protected:
	void StartAttack();
	void FireWeapon();
	void Fire();
	void StopAttack();
};