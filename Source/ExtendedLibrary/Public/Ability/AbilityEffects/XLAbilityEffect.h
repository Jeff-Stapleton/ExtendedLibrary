// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Ability/AbilityEffects/XLEffectOptions.h"
#include "XLAbilityEffect.generated.h"


UCLASS(config = Engine, hidecategories = (UObject, Length), Blueprintable, BlueprintType)
class AXLAbilityEffect : public AActor
{
	GENERATED_BODY()

public:
	AXLCharacter* Owner;

public:	
	AXLAbilityEffect();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options = NULL);

	virtual void Deactivate();

};
