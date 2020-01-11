// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAbilityEffect.h"

AXLAbilityEffect::AXLAbilityEffect()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXLAbilityEffect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLAbilityEffect::Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options)
{

}

void AXLAbilityEffect::Deactivate()
{
	Destroy();
}

