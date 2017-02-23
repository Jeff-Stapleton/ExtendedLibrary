// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLSelfAbility.h"

void UXLSelfAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
}

void UXLSelfAbility::Activate()
{
	if (MyPawn)
	{
		PlayUtilityAnimation();
		//PlayWeaponSound(GetWeaponEffects()->GetMeleeSound());
		ApplyCombatEffects();
	}
}

void UXLSelfAbility::Deactivate()
{
	for (TSubclassOf<class UXLAbilityEffect> EffectBP : AbilityEffects)
	{
		class UXLAbilityEffect* Effect = EffectBP.GetDefaultObject();
		Effect->Deactivate(MyPawn, MyPawn, 100);
	}
}

void UXLSelfAbility::ApplyCombatEffects()
{
	for (TSubclassOf<class UXLAbilityEffect> EffectBP : AbilityEffects)
	{
		class UXLAbilityEffect* Effect = EffectBP.GetDefaultObject();
		Effect->Activate(MyPawn, MyPawn, 100);
	}
}