// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacterResources.h"

UXLCharacterResources::UXLCharacterResources()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
	CurrentEnergy = MaxEnergy;
	CurrentStamina = MaxStamina;
	CurrentUltimate = MaxUltimate;
	CurrentShield = MaxShield;
}

void UXLCharacterResources::BeginPlay()
{
	Super::BeginPlay();
}

void UXLCharacterResources::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/*if ((CurrentHealth == ResourcesConfig.Health) || (CurrentMana == ResourcesConfig.Health))
	{
		CurrentHealth = (CurrentHealth >= ResourcesConfig.Health) ? (ResourcesConfig.Health) : (DeltaTime * GetHealthRegen() + (CurrentHealth));
		CurrentMana = (CurrentMana >= ResourcesConfig.Health) ? (ResourcesConfig.Mana) : (DeltaTime * GetManaRegen() + (CurrentMana));
	}*/
}



