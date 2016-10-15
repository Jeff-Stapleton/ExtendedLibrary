// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacterResources.h"

UXLCharacterResources::UXLCharacterResources()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	Character = Cast<AXLCharacter>(GetOwner());
}

void UXLCharacterResources::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	CurrentEnergy = MaxEnergy;
	CurrentStamina = MaxStamina;
	CurrentUltimate = MaxUltimate;
	CurrentShield = MaxShield;
}

void UXLCharacterResources::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	RegenerateHealth(DeltaTime);
	RegenerateStamina(DeltaTime);
	RegenerateEnergy(DeltaTime);
	RegenerateShield(DeltaTime);

	CooldownTimer(DeltaTime);
}

void UXLCharacterResources::RegenerateHealth(float DeltaTime)
{
	if (XLCharacterResourcesCan::RegenerateHealth(this))
	{
		if (Character->CharacterStats->HealthRegen > 0 && CurrentHealth < MaxHealth)
		{
			if (CurrentHealth < MaxHealth)
			{
				CurrentHealth += CurrentHealth + (Character->CharacterStats->HealthRegen * DeltaTime);
			}
			else
			{
				CurrentHealth = MaxHealth;
			}
		}
	}
}

void UXLCharacterResources::RegenerateStamina(float DeltaTime)
{
	if (XLCharacterResourcesCan::RegenerateStamina(this))
	{
		if (Character->CharacterStats->StaminaRegen > 0 && CurrentStamina < MaxStamina)
		{
			if (CurrentStamina < MaxStamina)
			{
				CurrentStamina += CurrentStamina + (Character->CharacterStats->StaminaRegen * DeltaTime);
			}
			else
			{
				CurrentStamina = MaxStamina;
			}
		}
	}
}

void UXLCharacterResources::RegenerateEnergy(float DeltaTime)
{
	if (XLCharacterResourcesCan::RegenerateEnergy(this))
	{
		if (Character->CharacterStats->EnergyRegen > 0 && CurrentEnergy < MaxEnergy)
		{
			if (CurrentEnergy < MaxEnergy)
			{
				CurrentEnergy += CurrentEnergy + (Character->CharacterStats->EnergyRegen  * DeltaTime);
			}
			else
			{
				CurrentEnergy = MaxEnergy;
			}
		}
	}
}

void UXLCharacterResources::RegenerateShield(float DeltaTime)
{
	if (XLCharacterResourcesCan::RegenerateShield(this))
	{
		if (Character->CharacterStats->ShieldRegen > 0 && CurrentShield < MaxShield)
		{
			if (CurrentShield < MaxShield)
			{
				CurrentShield += CurrentShield + (Character->CharacterStats->ShieldRegen * DeltaTime);
			}
			else
			{
				CurrentShield = MaxShield;
			}
		}
	}
}

void UXLCharacterResources::CooldownTimer(float DeltaTime)
{
	if (HealthCooldown > 0)
	{
		HealthCooldown -= DeltaTime;
	}
	if (StaminaCooldown > 0)
	{
		StaminaCooldown -= DeltaTime;
	}
	if (EnergyCooldown > 0)
	{
		EnergyCooldown -= DeltaTime;
	}
	if (ShieldCooldown > 0)
	{
		ShieldCooldown -= DeltaTime;
	}
}



