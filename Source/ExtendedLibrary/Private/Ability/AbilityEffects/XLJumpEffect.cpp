// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLJumpEffect.h"

AXLJumpEffect::AXLJumpEffect()
{
}

void AXLJumpEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, FXLEffectOptions* Options)
{
	if (Instigator && Target)
	{
		Cooldown = true;
		Character = Instigator;
		FVector Launch = FVector(0, 0, 1000);
		Target->LaunchCharacter(Launch, true, true);
	}
}

void AXLJumpEffect::Deactivate()
{
	if (Character)
	{
		Character->MovementComponent->ModifyJumpHeight(1.0f);
		Destroy();
	}
}