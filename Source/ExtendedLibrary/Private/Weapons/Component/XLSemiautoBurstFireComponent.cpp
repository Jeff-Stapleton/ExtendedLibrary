// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/Components/XLSemiautoBurstFireComponent.h"

UXLSemiautoBurstFireComponent::UXLSemiautoBurstFireComponent()
{
	bWantsInitializeComponent = true;
}

void UXLSemiautoBurstFireComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->ItemPrimaryStateDelegate.AddDynamic(this, &UXLSemiautoBurstFireComponent::DetermineAction);
}

void UXLSemiautoBurstFireComponent::DetermineAction()
{
	if (GetWeapon()->PrimaryState == EWeaponState::Firing)
	{
		//GetWeapon()->PlayFX(MuzzleFX, MuzzleFXPoint);
		//GetWeapon()->PlaySound(FireLoopSound);
		StartAttack();
	}
	else
	{
		//GetWeapon()->StopFX();
		//GetWeapon()->StopSound();
		StopAttack();
	}
}

void UXLSemiautoBurstFireComponent::StartAttack()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float AttackTime = LastAttackTime + TimeBetweenAttacks;
	if (LastAttackTime > 0.0f && TimeBetweenAttacks > 0.0f && AttackTime > CurrentTime)
	{
		GetWeapon()->GetWorldTimerManager().SetTimer(FiringTimer, this, &UXLSemiautoBurstFireComponent::FireWeapon, AttackTime - CurrentTime, false);
	}
	else
	{
		FireWeapon();
	}
}

void UXLSemiautoBurstFireComponent::FireWeapon()
{
	Fire();
	GetWeapon()->GetWorldTimerManager().SetTimer(BurstTimer, this, &UXLSemiautoBurstFireComponent::Fire, TimeBetweenBursts, true);
}

void UXLSemiautoBurstFireComponent::Fire()
{
	if (BurstCounter < NumberOfBursts)
	{
		if (XLRangedWeaponCan::Fire(GetWeapon()))
		{
			//GetWeapon()->FireEventDelegate.Broadcast();
			LastAttackTime = GetWorld()->GetTimeSeconds();
			GetWeapon()->PlayFX(MuzzleFX, MuzzleFXPoint);
			GetWeapon()->PlaySound(FireLoopSound);
		}
		BurstCounter++;
	}
	else
	{
		GetWeapon()->GetWorldTimerManager().ClearTimer(BurstTimer);
		BurstCounter = 0;
	}
}

void UXLSemiautoBurstFireComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

