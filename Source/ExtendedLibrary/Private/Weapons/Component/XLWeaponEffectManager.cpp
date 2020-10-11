// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Weapons/Components/XLWeaponEffectManager.h"

UXLWeaponEffectManager::UXLWeaponEffectManager()
{
	bWantsInitializeComponent = true;
}

void UXLWeaponEffectManager::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());
	Owner->WeaponStateDelegate.AddDynamic(this, &UXLWeaponEffectManager::DetermineAction);
}

void UXLWeaponEffectManager::DetermineAction()
{
	if (Owner->WeaponState == EWeaponState::Firing)
	{
		ActivateMuzzlePSC();
	}
	else
	{
		DeactivateMuzzlePSC();
	}
}

void UXLWeaponEffectManager::ActivateMuzzlePSC_Implementation()
{
	if (MuzzleFX && MuzzlePSC == NULL)
	{
		MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, Owner->Mesh3P, MuzzleFXPoint);
	}
}

void UXLWeaponEffectManager::DeactivateMuzzlePSC_Implementation()
{
	if (MuzzlePSC)
	{
		MuzzlePSC->DeactivateSystem();
		MuzzlePSC = NULL;
	}
}
