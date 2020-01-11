// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XLAbilityEffect.h"
#include "Ability/AbilityEffects/XLEffectOptions.h"
#include "XLHoverEffect.generated.h"

/**
 * 
 */
UCLASS()
class AXLHoverEffect : public AXLAbilityEffect
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

public:
	AXLCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float Duration;

	FTimerHandle TimerHandle_Duration;

public:
	AXLHoverEffect();

	void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options = NULL) override;
	
	void Deactivate() override;

};
