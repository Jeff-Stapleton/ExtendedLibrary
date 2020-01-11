// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponEffectManager.h"

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

void UXLWeaponEffectManager::ActivateMuzzlePSC()
{
	if (MuzzleFX && MuzzlePSC == NULL)
	{
		MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, Owner->Mesh3P, MuzzleFXPoint);
	}
}

void UXLWeaponEffectManager::DeactivateMuzzlePSC()
{
	if (MuzzlePSC)
	{
		MuzzlePSC->DeactivateSystem();
		MuzzlePSC = NULL;
	}
}