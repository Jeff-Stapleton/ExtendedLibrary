// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Enums/XLAmmoComponentState.h"
#include "Weapons/Components/XLReloadComponent.h"

UXLReloadComponent::UXLReloadComponent()
{
    bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UXLReloadComponent::InitializeComponent()
{
    Super::InitializeComponent();

	CurrentAmmo = AmmoConfig.MaxAmmo;
	CurrentClipAmmo = AmmoConfig.MaxClipAmmo;

	AmmoComponentState = EAmmoComponentState::FullMagazine;
}

//void UXLReloadComponent::DetermineAction()
//{
//	if (Owner->WeaponState == EWeaponState::Reloading)
//	{
//		float OriginalDuration = ReloadAnim->CalculateSequenceLength();
//		float Rate = OriginalDuration / ReloadDuration;
//
//		//Owner->Character->PlayAnimation(ReloadAnim, Rate);
//		//Owner->PlaySound(ReloadSound);
//		//Owner->GetWorldTimerManager().SetTimer(ReloadTimer, this, &UXLReloadComponent::Reload, ReloadDuration, false);
//	}
//}

void UXLReloadComponent::ConsumeAmmo()
{
	if (!AmmoConfig.InfiniteClip)
	{
		CurrentClipAmmo--;
		AmmoComponentState = EAmmoComponentState::PartialMagazine;
	}

	if (CurrentAmmo <= 0 && CurrentClipAmmo <= 0)
	{
		AmmoComponentState = EAmmoComponentState::OutOfAmmo;
	}
	else if (CurrentClipAmmo <= 0)
	{
		AmmoComponentState = EAmmoComponentState::EmptyMagazine;
	}
}

void UXLReloadComponent::Reload()
{
	float ClipDelta = FMath::Min(AmmoConfig.MaxClipAmmo - CurrentClipAmmo, CurrentAmmo - CurrentClipAmmo);
	if (ClipDelta > 0)
	{
		CurrentClipAmmo += ClipDelta;

		if (!AmmoConfig.InfiniteAmmo)
		{
			CurrentAmmo -= ClipDelta;
		}

		AmmoComponentState = CurrentClipAmmo == AmmoConfig.MaxClipAmmo ? EAmmoComponentState::FullMagazine : EAmmoComponentState::PartialMagazine;
	}
}

//bool UXLReloadComponent::ServerConsumeAmmo_Validate()
//{
//	return true;
//}
//
//void UXLReloadComponent::ServerConsumeAmmo_Implementation()
//{
//	CurrentClipAmmo--;
//}
//
//bool UXLReloadComponent::ServerReload_Validate(float ClipDelta)
//{
//	return true;
//}
//
//void UXLReloadComponent::ServerReload_Implementation(float ClipDelta)
//{
//	CurrentClipAmmo += ClipDelta;
//
//	if (!AmmoConfig.InfiniteAmmo)
//	{
//		CurrentAmmo -= ClipDelta;
//	}
//}

//void UXLReloadComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME_CONDITION(UXLReloadComponent, MaxAmmo, COND_OwnerOnly);
//}
