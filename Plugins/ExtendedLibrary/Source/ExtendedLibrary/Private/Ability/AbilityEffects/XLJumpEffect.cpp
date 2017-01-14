// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLJumpEffect.h"

UXLJumpEffect::UXLJumpEffect()
{
}

void UXLJumpEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->MovementComponent->ModifyJumpHeight(3.0f);
		Target->Jump();
	}
}

void UXLJumpEffect::Deactivate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->MovementComponent->ModifyJumpHeight(1.0f);
	}
}