// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLReloadComponent.h"

UXLReloadComponent::UXLReloadComponent()
{
    bWantsInitializeComponent = true;
	bReplicates = true;
}

void UXLReloadComponent::InitializeComponent()
{
    Super::InitializeComponent();

	CurrentAmmo = MaxAmmo;
	CurrentClipAmmo = MaxClipAmmo;

	Owner = Cast<AXLRangedWeapon>(GetOwner());

	Owner->WeaponStateDelegate.AddDynamic(this, &UXLReloadComponent::DetermineAction);
	Owner->FireEventDelegate.AddDynamic(this, &UXLReloadComponent::ConsumeAmmo);
}

void UXLReloadComponent::DetermineAction()
{
	if (Owner->WeaponState == EWeaponState::Reloading)
	{
		float OriginalDuration = ReloadAnim->CalculateSequenceLength();
		float Rate = OriginalDuration / ReloadDuration;

		Owner->Character->PlayAnimMontage(ReloadAnim, Rate);
		Owner->PlaySound(ReloadSound);
		Owner->GetWorldTimerManager().SetTimer(ReloadTimer, this, &UXLReloadComponent::Reload, ReloadDuration, false);
	}
}

void UXLReloadComponent::ConsumeAmmo()
{
	if (!InfiniteClip)
	{
		CurrentClipAmmo--;
	}
	if (CurrentClipAmmo <= 0)
	{
		Owner->WeaponState = EWeaponState::OutOfAmmo;
		Owner->WeaponStateDelegate.Broadcast();
	}
}

void UXLReloadComponent::Reload()
{
	float ClipDelta = FMath::Min(MaxClipAmmo - CurrentClipAmmo, CurrentAmmo - CurrentClipAmmo);
	if (ClipDelta > 0)
	{
		CurrentClipAmmo += ClipDelta;

		if (!InfiniteAmmo)
		{
			CurrentAmmo -= ClipDelta;
		}
	}
	Owner->WeaponState = EWeaponState::Idle;
	Owner->WeaponStateDelegate.Broadcast();
}


void UXLReloadComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UXLReloadComponent, MaxAmmo, COND_OwnerOnly);
}
