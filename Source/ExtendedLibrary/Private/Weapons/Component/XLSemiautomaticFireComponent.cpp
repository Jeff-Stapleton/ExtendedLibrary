// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Controllers/XLAIController.h"
#include "Camera/XLCamera.h"
#include "Characters/XLPlayerCharacter.h"
#include "Projectiles/XLProjectile.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Weapons/Components/XLSemiautomaticFireComponent.h"

UXLSemiautomaticFireComponent::UXLSemiautomaticFireComponent()
{	
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UXLSemiautomaticFireComponent::DetermineAction()
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
	if (AmmoComponent->AmmoComponentState != EAmmoComponentState::EmptyMagazine && AmmoComponent->AmmoComponentState != EAmmoComponentState::OutOfAmmo)
	{
		const FVector Start = GetWeapon()->GetSocketLocation(SpawnPoint);
		const FVector End = AimingComponent->GetAdjustedAim();

		ServerFireProjectile(Start, End);
		AmmoComponent->ConsumeAmmo(); //SECURITY VULNERABILITY: Handling ammo client side, potential for hackers to manipulate this value

		LastAttackTime = GetWorld()->GetTimeSeconds();
		GetWeapon()->PlayFX(MuzzleFX, MuzzleFXPoint);
		GetWeapon()->PlaySound(FireSound);
	}
}

void UXLSemiautomaticFireComponent::StopAttack()
{
	GetWeapon()->GetWorldTimerManager().ClearTimer(FiringTimer);
}

bool UXLSemiautomaticFireComponent::ServerFireProjectile_Validate(FVector Origin, FVector ShootDir)
{
	return true;
}

void UXLSemiautomaticFireComponent::ServerFireProjectile_Implementation(FVector Origin, FVector ShootDir)
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
		AmmoComponent->ConsumeAmmo();
	}
}
