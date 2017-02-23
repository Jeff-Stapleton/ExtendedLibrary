// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "XLAbilityEffect.generated.h"


UCLASS(config = Engine, hidecategories = (UObject, Length), Blueprintable, BlueprintType)
class UXLAbilityEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXLAbilityEffect();
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, float Strength, float Duration = 0.0f);

	virtual void Deactivate(class AXLCharacter* Instigator, class AXLCharacter* Target, float Strength, float Duration = 0.0f);

};
