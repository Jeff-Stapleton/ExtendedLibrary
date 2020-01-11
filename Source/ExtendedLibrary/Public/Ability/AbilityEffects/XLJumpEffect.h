// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XLAbilityEffect.h"
#include "Ability/AbilityEffects/XLEffectOptions.h"
#include "XLJumpEffect.generated.h"

/**
 * 
 */
UCLASS()
class AXLJumpEffect : public AXLAbilityEffect
{
	GENERATED_BODY()

public:
	AXLCharacter* Character;

	bool Cooldown = false;
	
public:
	AXLJumpEffect();

	void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options = NULL) override;
	
	void Deactivate() override;

};
