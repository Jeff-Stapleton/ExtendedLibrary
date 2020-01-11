// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLSelfAbility.h"

void AXLSelfAbility::Activate()
{
	if (MyPawn)
	{
		PlayUtilityAnimation();
		//PlayWeaponSound(GetWeaponEffects()->GetMeleeSound());
		ApplyCombatEffects();
	}
}

void AXLSelfAbility::Deactivate()
{
	for (TSubclassOf<class AXLAbilityEffect> EffectBP : AbilityEffects)
	{
		class AXLAbilityEffect* Effect = EffectBP.GetDefaultObject();
		Effect->Deactivate();
	}
}

void AXLSelfAbility::ApplyCombatEffects()
{

	for (TSubclassOf<class AXLAbilityEffect> EffectBP : AbilityEffects)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		class AXLAbilityEffect* Effect = GetWorld()->SpawnActor<AXLAbilityEffect>(EffectBP, SpawnInfo);
		Effect->Activate(MyPawn, MyPawn);
	}
}
