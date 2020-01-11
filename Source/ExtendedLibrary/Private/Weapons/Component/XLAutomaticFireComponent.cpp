// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAutomaticFireComponent.h"

UXLAutomaticFireComponent::UXLAutomaticFireComponent()
{
	bWantsInitializeComponent = true;
}

void UXLAutomaticFireComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->WeaponStateDelegate.AddDynamic(this, &UXLAutomaticFireComponent::DetermineAction);
}

void UXLAutomaticFireComponent::DetermineAction()
{
	if (GetWeapon()->WeaponState == EWeaponState::Firing)
	{
		StartAttack();
	}
	else
	{
		StopAttack();
	}
}

void UXLAutomaticFireComponent::StartAttack()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float AttackTime = LastAttackTime + TimeBetweenAttacks;
	if (LastAttackTime > 0.0f && TimeBetweenAttacks > 0.0f && AttackTime > CurrentTime)
	{
		GetWeapon()->GetWorldTimerManager().SetTimer(FiringTimer, this, &UXLAutomaticFireComponent::FireWeapon, AttackTime - CurrentTime, false);
	}
	else
	{
		FireWeapon();
	}
}

void UXLAutomaticFireComponent::FireWeapon()
{
	Fire();
	GetWeapon()->GetWorldTimerManager().SetTimer(FiringTimer, this, &UXLAutomaticFireComponent::Fire, TimeBetweenAttacks, true);
}

void UXLAutomaticFireComponent::Fire()
{
	if (XLRangedWeaponCan::Fire(GetWeapon()))
	{
		GetWeapon()->FireEventDelegate.Broadcast();
		LastAttackTime = GetWorld()->GetTimeSeconds();
	}
}

void UXLAutomaticFireComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

