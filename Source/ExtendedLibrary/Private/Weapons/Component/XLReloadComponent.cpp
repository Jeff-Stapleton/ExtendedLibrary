// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLReloadComponent.h"

UXLReloadComponent::UXLReloadComponent()
{
    bWantsInitializeComponent = true;
}

void UXLReloadComponent::InitializeComponent()
{
    Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());

	Owner->FireEventDelegate.AddDynamic(this, &UXLReloadComponent::ConsumeAmmo);
	Owner->ReloadEventDelegate.AddDynamic(this, &UXLReloadComponent::Reload);
}

void UXLReloadComponent::OnRegister()
{
	Super::OnRegister();
}

void UXLReloadComponent::ConsumeAmmo()
{
	if (!Owner->WeaponStats->InfiniteClip)
	{
		Owner->WeaponStats->CurrentClipAmmo--;
	}
}

void UXLReloadComponent::Reload()
{
	float ClipDelta = FMath::Min(Owner->WeaponStats->MaxClipAmmo - Owner->WeaponStats->CurrentClipAmmo, Owner->WeaponStats->CurrentAmmo - Owner->WeaponStats->CurrentClipAmmo);
	if (ClipDelta > 0)
	{
		Owner->WeaponStats->CurrentClipAmmo += ClipDelta;

		if (!Owner->WeaponStats->InfiniteAmmo)
		{
			Owner->WeaponStats->CurrentAmmo -= ClipDelta;
		}
	}
}



