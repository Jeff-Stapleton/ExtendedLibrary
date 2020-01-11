// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPhaseEffect.h"

AXLPhaseEffect::AXLPhaseEffect()
{
}

void AXLPhaseEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, FXLEffectOptions* Options)
{
	if (Instigator && Target)
	{
		Character = Instigator;
		Target->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
		Target->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	}
}

void AXLPhaseEffect::Deactivate()
{
	if (Character)
	{
		Character->GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
		Character->GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
		Destroy();
	}
}