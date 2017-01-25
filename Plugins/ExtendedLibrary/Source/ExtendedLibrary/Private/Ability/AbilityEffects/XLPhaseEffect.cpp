// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPhaseEffect.h"

UXLPhaseEffect::UXLPhaseEffect()
{
}

void UXLPhaseEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
		Target->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	}
}

void UXLPhaseEffect::Deactivate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Target->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
		Target->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	}
}