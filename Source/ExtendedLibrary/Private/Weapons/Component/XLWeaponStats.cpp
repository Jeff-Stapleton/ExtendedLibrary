// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponStats.h"

UXLWeaponStats::UXLWeaponStats()
{
	bReplicates = true;
}

void UXLWeaponStats::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpread = MinSpread;
}

void UXLWeaponStats::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXLWeaponStats, MaxAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLWeaponStats, CurrentAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLWeaponStats, MaxClipAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLWeaponStats, CurrentClipAmmo, COND_OwnerOnly);
}