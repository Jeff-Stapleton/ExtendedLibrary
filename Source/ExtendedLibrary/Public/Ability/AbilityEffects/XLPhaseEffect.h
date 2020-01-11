// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XLAbilityEffect.h"
#include "Ability/AbilityEffects/XLEffectOptions.h"
#include "XLPhaseEffect.generated.h"

/**
 * 
 */
UCLASS()
class AXLPhaseEffect : public AXLAbilityEffect
{
	GENERATED_BODY()
		
	AXLCharacter* Character;
	
public:
	FCollisionResponseContainer Responses;

	AXLPhaseEffect();

	void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options = NULL) override;
	
	void Deactivate() override;

};
