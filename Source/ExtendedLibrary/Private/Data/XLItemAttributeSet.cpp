// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Data/XLItemAttributeSet.h"

UXLItemAttributeSet::UXLItemAttributeSet()
	: Damage(1.f)
	, FOVMultiplier(1.f)
{}

void UXLItemAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLItemAttributeSet, Damage);
	DOREPLIFETIME(UXLItemAttributeSet, FOVMultiplier);
}

void UXLItemAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLItemAttributeSet, Damage, OldDamage);
}

void UXLItemAttributeSet::OnRep_FOVMultiplier(const FGameplayAttributeData& OldFOVMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLItemAttributeSet, FOVMultiplier, OldFOVMultiplier);
}