// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Weapons/XLRangedWeapon.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"

UXLAmmoComponent::UXLAmmoComponent()
{
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
	bNetAddressable = true;
}

void UXLAmmoComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UXLAmmoComponent::BeginPlay()
{
	Super::BeginPlay();
}

class AXLRangedWeapon* UXLAmmoComponent::GetWeapon()
{
	return Cast<AXLRangedWeapon>(GetOwner());
}

void UXLAmmoComponent::Reload()
{

}

void UXLAmmoComponent::ConsumeAmmo()
{

}

void UXLAmmoComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXLAmmoComponent, CurrentAmmo, COND_OwnerOnly);
	//DOREPLIFETIME_CONDITION(UXLAmmoComponent, MaxClipAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLAmmoComponent, CurrentClipAmmo, COND_OwnerOnly);
}
