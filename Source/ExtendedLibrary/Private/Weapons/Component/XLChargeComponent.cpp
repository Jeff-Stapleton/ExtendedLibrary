// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Controllers/XLAIController.h"
#include "Camera/XLCamera.h"
#include "Characters/XLPlayerCharacter.h"
#include "Projectiles/XLProjectile.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Data/Character/XLCharacterResources.h"
#include "Weapons/Components/XLChargeComponent.h"

UXLChargeComponent::UXLChargeComponent()
{	
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UXLChargeComponent::StartAttack()
{
	GetWeapon()->GetWorldTimerManager().SetTimer(ChargeTimer, this, &UXLChargeComponent::FireWeapon, ChargeTime, false);
}

void UXLChargeComponent::FireWeapon()
{
	ServerFireProjectile();
}

void UXLChargeComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

bool UXLChargeComponent::ServerFireProjectile_Validate()
{
	return true;
}

void UXLChargeComponent::ServerFireProjectile_Implementation()
{
	GetWeapon()->Character->CharacterResources->CurrentHealth = GetWeapon()->Character->CharacterResources->MaxHealth;
}
