// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLHoverEffect.h"

UXLHoverEffect::UXLHoverEffect()
{
}

void UXLHoverEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
	}
}

void UXLHoverEffect::Deactivate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}