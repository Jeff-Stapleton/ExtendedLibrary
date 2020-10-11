// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Data/Character/XLCharacterStats.h"

UXLCharacterStats::UXLCharacterStats()
{
	SetIsReplicatedByDefault(true);
}

void UXLCharacterStats::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLCharacterStats, HealthRegen);
	DOREPLIFETIME(UXLCharacterStats, EnergyRegen);
	DOREPLIFETIME(UXLCharacterStats, StaminaRegen);
	DOREPLIFETIME(UXLCharacterStats, ShieldRegen);
	DOREPLIFETIME(UXLCharacterStats, AttackSpeed);
	DOREPLIFETIME(UXLCharacterStats, AttackPower);
	DOREPLIFETIME(UXLCharacterStats, CooldownReduction);
	DOREPLIFETIME(UXLCharacterStats, AbilityPower);
	DOREPLIFETIME(UXLCharacterStats, PhysicalDefense);
	DOREPLIFETIME(UXLCharacterStats, EnergyDefense)
}


