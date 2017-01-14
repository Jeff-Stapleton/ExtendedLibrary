// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability/XLAbility.h"
#include "XLSelfAbility.generated.h"

/**
 * 
 */
UCLASS()
class UXLSelfAbility : public UXLAbility
{
	GENERATED_BODY()
	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Activate();

	void Deactivate();

	void ApplyCombatEffects();	
};
