// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLBlastEffect.h"

AXLBlastEffect::AXLBlastEffect()
{
}

void AXLBlastEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, FXLEffectOptions* Options)
{
	if (Instigator && Options)
	{
		UGameplayStatics::ApplyRadialDamageWithFalloff(this, MaxDamage, MinDamage, Options->Origin, InnerRadius, OutterRadius, DamageFalloff, UDamageType::StaticClass(), TArray<AActor*>(), Instigator, Instigator->Controller);
	}
}