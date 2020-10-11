// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Weapons/Components/XLShellAmmoComponent.h"

UXLShellAmmoComponent::UXLShellAmmoComponent()
{
	bWantsInitializeComponent = true;
}

void UXLShellAmmoComponent::InitializeComponent()
{
    Super::InitializeComponent();

	CurrentAmmo = AmmoConfig.MaxAmmo;
	CurrentClipAmmo = AmmoConfig.MaxClipAmmo;

	GetWeapon()->WeaponStateDelegate.AddDynamic(this, &UXLShellAmmoComponent::DetermineAction);
	GetWeapon()->FireEventDelegate.AddDynamic(this, &UXLShellAmmoComponent::ConsumeAmmo);
}

void UXLShellAmmoComponent::DetermineAction()
{
	if (GetWeapon()->WeaponState == EWeaponState::Reloading)
	{
		AnimationRate = ReloadAnim->CalculateSequenceLength() / ReloadDuration;
		Reload();
	}
}

void UXLShellAmmoComponent::Reload()
{
	GetWeapon()->Character->PlayAnimation(ReloadAnim, AnimationRate);
	GetWeapon()->PlaySound(ReloadSound);
	GetWeapon()->GetWorldTimerManager().SetTimer(ReloadTimer, this, &UXLShellAmmoComponent::LoadShell, ReloadDuration, false);
}

void UXLShellAmmoComponent::LoadShell()
{
	if (CurrentClipAmmo < AmmoConfig.MaxClipAmmo && CurrentAmmo > 0)
	{
		CurrentClipAmmo++;
		if (!InfiniteAmmo)
		{
			CurrentAmmo--;
		}
	}

	if (CurrentClipAmmo < AmmoConfig.MaxClipAmmo && CurrentAmmo > 0)
	{
		Reload();
	}
	else
	{
		GetWeapon()->GetWorldTimerManager().ClearTimer(ReloadTimer);
		GetWeapon()->WeaponState = EWeaponState::Idle;
		GetWeapon()->WeaponStateDelegate.Broadcast();
	}
}

void UXLShellAmmoComponent::ConsumeAmmo()
{
	if (!InfiniteClip)
	{
		CurrentClipAmmo--;
	}
	if (CurrentClipAmmo <= 0)
	{
		GetWeapon()->WeaponState = EWeaponState::OutOfAmmo;
		GetWeapon()->WeaponStateDelegate.Broadcast();
	}
}

void UXLShellAmmoComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXLShellAmmoComponent, MaxAmmo, COND_OwnerOnly);
}
