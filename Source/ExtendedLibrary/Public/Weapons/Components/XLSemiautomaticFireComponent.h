#pragma once

#include "XLFireComponent.h"
#include "XLRangedWeaponCan.h"
#include "XLSemiautomaticFireComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSemiautomaticFireComponent : public UXLFireComponent
{
	GENERATED_BODY()

	UXLSemiautomaticFireComponent();
	void InitializeComponent() override;

public:
	/** The amount of time that must pass before being able to attack again */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenAttacks = 0.40f;

	float LastAttackTime = 0.0f;
	FTimerHandle FiringTimer;

public:
	UFUNCTION()
	void DetermineAction();

protected:
	void StartAttack();
	void FireWeapon();
	void StopAttack();
};