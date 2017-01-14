// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAbilityEffect.h"

UXLAbilityEffect::UXLAbilityEffect()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLAbilityEffect::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UXLAbilityEffect::Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, float Strength, float Duration)
{
}

void UXLAbilityEffect::Deactivate(class AXLCharacter* Instigator, class AXLCharacter* Target, float Strength, float Duration)
{
}

