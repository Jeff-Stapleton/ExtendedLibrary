// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Effects/XLImpactEffect.h"
#include "Weapons/Components/XLWeaponEffectManager.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"
#include "Weapons/Components/Interfaces/XLProjectileComponent.h"
#include "Weapons/Components/XLRecoilComponent.h"
#include "Weapons/Components/Interfaces/XLTargetingComponent.h"
#include "Weapons/XLRangedWeapon.h"

AXLRangedWeapon::AXLRangedWeapon()
{
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}

void AXLRangedWeapon::BeginPlay()
{
	Super::BeginPlay();

	//Some of these components reference each other. could run into some async issues
	ReloadComponent = NewObject<UXLAmmoComponent>(this, ReloadComponentBP, FName(TEXT("AmmoComponent")));
	AimingComponent = NewObject<UXLAimingComponent>(this, AimingComponentBP, FName(TEXT("AimingComponent")));
	FiringComponent = NewObject<UXLFireComponent>(this, FiringComponentBP, FName(TEXT("FiringComponent")));
	ProjectileComponent = NewObject<UXLProjectileComponent>(this, ProjectileComponentBP, FName(TEXT("ProjectileComponent")));
	RecoilComponent = NewObject<UXLRecoilComponent>(this, RecoilComponentBP, FName(TEXT("RecoilComponent")));
	TargetingComponent = NewObject<UXLTargetingComponent>(this, TargetingComponentBP, FName(TEXT("TargetingComponent")));

	ReloadComponent->RegisterComponent();
	AimingComponent->RegisterComponent();
	FiringComponent->RegisterComponent();
	ProjectileComponent->RegisterComponent();
	RecoilComponent->RegisterComponent();
	TargetingComponent->RegisterComponent();
}

void AXLRangedWeapon::Destroyed()
{
	Super::Destroyed();

	//StopFX();
}

void AXLRangedWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	if (NewOwner)
	{
		Character = Cast<AXLCharacter>(NewOwner);
		Character->LookingDelegate.AddDynamic(this, &AXLRangedWeapon::OnAiming);
	}
}

/////////////////////////////////////////// Input handlers //////////////////////////////////////////

void AXLRangedWeapon::OnAiming()
{
	WeaponAimDelegate.Broadcast();
}

void AXLRangedWeapon::StartAiming()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerStartAiming();
		return;
	}

	TargetingState = ETargetingState::ADS;
	TargetingStateDelegate.Broadcast();
}
bool AXLRangedWeapon::ServerStartAiming_Validate()
{
	return true;
}
void AXLRangedWeapon::ServerStartAiming_Implementation()
{
	StartAiming();
}

void AXLRangedWeapon::StopAiming()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerStopAiming();
		return;
	}

	TargetingState = ETargetingState::Ready;
	TargetingStateDelegate.Broadcast();
}
bool AXLRangedWeapon::ServerStopAiming_Validate()
{
	return true;
}
void AXLRangedWeapon::ServerStopAiming_Implementation()
{
	StopAiming();
}

void AXLRangedWeapon::StartAttack()
{
	if (XLRangedWeaponCan::Fire(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStartAttack();
			return;
		}

		WeaponState = EWeaponState::Firing;
		WeaponStateDelegate.Broadcast();
	}
}
bool AXLRangedWeapon::ServerStartAttack_Validate()
{
	return true;
}
void AXLRangedWeapon::ServerStartAttack_Implementation()
{
	StartAttack();
}

void AXLRangedWeapon::StopAttack()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerStopAttack();
		return;
	}
	if (WeaponState != EWeaponState::OutOfAmmo)
	{
		WeaponState = EWeaponState::Idle;
	}
	WeaponStateDelegate.Broadcast();
}
bool AXLRangedWeapon::ServerStopAttack_Validate()
{
	return true;
}
void AXLRangedWeapon::ServerStopAttack_Implementation()
{
	StopAttack();
}

void AXLRangedWeapon::Reload()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerReload();
		return;
	}

	WeaponState = EWeaponState::Reloading;
	WeaponStateDelegate.Broadcast();
}
bool AXLRangedWeapon::ServerReload_Validate()
{
	return true;
}
void AXLRangedWeapon::ServerReload_Implementation()
{
	Reload();
}

////////////////////////////////////////////// Actions /////////////////////////////////////////////

void AXLRangedWeapon::ApplyAttackForce(const FHitResult& Impact)
{
	if ((Impact.GetComponent() != nullptr) && Impact.GetComponent()->IsSimulatingPhysics())
	{
		//Impact.GetComponent()->AddForce((WeaponStats->Force * Impact.ImpactNormal), Impact.BoneName);
	}
}

////////////////////////////////////////////// Helpers /////////////////////////////////////////////

FVector AXLRangedWeapon::GetMuzzleLocation()
{
	if (Character && Character->IsLocallyControlled())
	{
		class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);
		if (MyPC && MyPC->IsFirstPerson)
		{
			return Mesh1P->GetSocketLocation(FName(TEXT("Muzzle")));
		}
	}
	return Mesh3P->GetSocketLocation(FName(TEXT("Muzzle")));
}

float AXLRangedWeapon::GetCurrentSpread() const
{
	//float FinalSpread = WeaponStats->MinSpread + CurrentWeaponSpread;
	//if (Character->TargetingState == ETargetingState::ADS)
	//{
	//	FinalSpread *= WeaponStats->SpreadModifier;
	//}
	//return FinalSpread;
	return 0.0f;
}

void AXLRangedWeapon::SetCurrentSpread()
{
	//CurrentWeaponSpread = FMath::Min(WeaponStats->MaxSpread, CurrentWeaponSpread + WeaponStats->SpreadRate);
	CurrentWeaponSpread = 0.0f;
}

//////////////////////////////////////////// Replication ///////////////////////////////////////////

void AXLRangedWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLRangedWeapon, WeaponState);
	DOREPLIFETIME(AXLRangedWeapon, TargetingState);
}
