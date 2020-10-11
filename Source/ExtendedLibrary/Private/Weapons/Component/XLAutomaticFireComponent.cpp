// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Controllers/XLAIController.h"
#include "Camera/XLCamera.h"
#include "Characters/XLPlayerCharacter.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Weapons/Components/XLAutomaticFireComponent.h"

UXLAutomaticFireComponent::UXLAutomaticFireComponent()
{
	bWantsInitializeComponent = true;
}

void UXLAutomaticFireComponent::DetermineAction()
{
	if (GetWeapon()->PrimaryState == EItemPrimaryState::Activated)
	{
		StartAttack();
	}
	else if (GetWeapon()->PrimaryState == EItemPrimaryState::Reloading)
	{
		AmmoComponent->Reload();
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
	if (AmmoComponent->AmmoComponentState != EAmmoComponentState::EmptyMagazine && AmmoComponent->AmmoComponentState != EAmmoComponentState::OutOfAmmo)
	{
		Fire();
		GetWeapon()->GetWorldTimerManager().SetTimer(FiringTimer, this, &UXLAutomaticFireComponent::Fire, TimeBetweenAttacks, true);
	}
	else
	{

	}
}

void UXLAutomaticFireComponent::Fire()
{
	if (AmmoComponent->AmmoComponentState != EAmmoComponentState::EmptyMagazine && AmmoComponent->AmmoComponentState != EAmmoComponentState::OutOfAmmo)
	{
		const FVector Start = GetWeapon()->GetSocketLocation("Muzzle");
		const FVector End = AimingComponent->GetAdjustedAim();

		ServerFireProjectile(Start, End);
		AmmoComponent->ConsumeAmmo(); //SECURITY VULNERABILITY: Handling ammo client side, potential for hackers to manipulate this value

		LastAttackTime = GetWorld()->GetTimeSeconds();
		GetWeapon()->PlayFX(MuzzleFX, MuzzleFXPoint);
		GetWeapon()->PlaySound(FireSound);
	}
}

void UXLAutomaticFireComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

bool UXLAutomaticFireComponent::ServerFireProjectile_Validate(FVector Origin, FVector ShootDir)
{
	return true;
}

void UXLAutomaticFireComponent::ServerFireProjectile_Implementation(FVector Origin, FVector ShootDir)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLProjectile* jeff = Cast<AXLProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AmmoComponent->Projectile, SpawnTM));
	if (jeff)
	{
		//Projectile->Instigator = Instigator;
		jeff->SetOwner(GetWeapon());
		//AppyProjectileData(jeff); // Thinking about making projectiles completely independent
		FVector test = (ShootDir - Origin).GetSafeNormal();
		jeff->InitVelocity(test);

		UGameplayStatics::FinishSpawningActor(jeff, SpawnTM);
	}
}
