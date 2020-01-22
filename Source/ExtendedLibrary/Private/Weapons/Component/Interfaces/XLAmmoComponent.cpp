// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAmmoComponent.h"

UXLAmmoComponent::UXLAmmoComponent()
{
	bWantsInitializeComponent = true;
}

void UXLAmmoComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

class AXLRangedWeapon* UXLAmmoComponent::GetWeapon()
{
	return Cast<AXLRangedWeapon>(GetOwner());
}

void UXLAmmoComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXLAmmoComponent, CurrentAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLAmmoComponent, MaxClipAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UXLAmmoComponent, CurrentClipAmmo, COND_OwnerOnly);
}
