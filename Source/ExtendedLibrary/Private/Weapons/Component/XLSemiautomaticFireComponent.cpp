// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLSemiautomaticFireComponent.h"

UXLSemiautomaticFireComponent::UXLSemiautomaticFireComponent()
{
	bWantsInitializeComponent = true;
}

void UXLSemiautomaticFireComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->WeaponStateDelegate.AddDynamic(this, &UXLSemiautomaticFireComponent::DetermineAction);
}

void UXLSemiautomaticFireComponent::DetermineAction()
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

void UXLSemiautomaticFireComponent::StartAttack()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float AttackTime = LastAttackTime + TimeBetweenAttacks;
	if (LastAttackTime > 0.0f && TimeBetweenAttacks > 0.0f && AttackTime > CurrentTime)
	{
		GetWeapon()->GetWorldTimerManager().SetTimer(FiringTimer, this, &UXLSemiautomaticFireComponent::FireWeapon, AttackTime - CurrentTime, false);
	}
	else
	{
		FireWeapon();
	}
}

void UXLSemiautomaticFireComponent::FireWeapon()
{
	if (XLRangedWeaponCan::Fire(GetWeapon()))
	{
		GetWeapon()->FireEventDelegate.Broadcast();
		LastAttackTime = GetWorld()->GetTimeSeconds();
	}
}

void UXLSemiautomaticFireComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

