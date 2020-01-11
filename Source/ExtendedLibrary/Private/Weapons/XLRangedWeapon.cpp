// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLRangedWeapon.h"
#include "XLImpactEffect.h"
#include "XLWeaponEffectManager.h"

AXLRangedWeapon::AXLRangedWeapon()
{
	WeaponAnimations = CreateDefaultSubobject<UXLWeaponAnimationManager>(TEXT("WeaponAnimations"));
	WeaponEffects = CreateDefaultSubobject<UXLWeaponEffectManager>(TEXT("WeaponEffects"));
	WeaponSounds = CreateDefaultSubobject<UXLWeaponSoundManager>(TEXT("WeaponSounds"));
	WeaponStats = CreateDefaultSubobject<UXLWeaponStats>(TEXT("WeaponStats"));

	WeaponStats->CurrentAmmo = WeaponStats->MaxAmmo;
	WeaponStats->CurrentClipAmmo = WeaponStats->MaxClipAmmo;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}

void AXLRangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	//Some of these components reference each other. could run into some async issues
	AimingComponent = NewObject<UXLAimingComponent>(this, AimingComponentBP, FName(TEXT("AimingComponent")));
	FiringComponent = NewObject<UXLFireComponent>(this, FiringComponentBP, FName(TEXT("FiringComponent")));
	ProjectileComponent = NewObject<UXLProjectileComponent>(this, ProjectileComponentBP, FName(TEXT("ProjectileComponent")));
	ReloadComponent = NewObject<UXLReloadComponent>(this, ReloadComponentBP, FName(TEXT("ReloadComponent")));
	RecoilComponent = NewObject<UXLRecoilComponent>(this, RecoilComponentBP, FName(TEXT("RecoilComponent")));

	AimingComponent->RegisterComponent();
	FiringComponent->RegisterComponent();
	ProjectileComponent->RegisterComponent();
	ReloadComponent->RegisterComponent();
	RecoilComponent->RegisterComponent();
}

void AXLRangedWeapon::Destroyed()
{
	Super::Destroyed();

	StopFX();
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

void AXLRangedWeapon::StartAttack()
{
	if (XLRangedWeaponCan::Fire(this))
	{
		if (Role < ROLE_Authority)
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
	if (Role < ROLE_Authority)
	{
		ServerStopAttack();
		return;
	}

	WeaponState = EWeaponState::Idle;
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
	if (Role < ROLE_Authority)
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
		Impact.GetComponent()->AddForce((WeaponStats->Force * Impact.ImpactNormal), Impact.BoneName);
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
	float FinalSpread = WeaponStats->MinSpread + CurrentWeaponSpread;
	if (Character->TargetingState == ETargetingState::ADS)
	{
		FinalSpread *= WeaponStats->SpreadModifier;
	}
	return FinalSpread;
}

void AXLRangedWeapon::SetCurrentSpread()
{
	CurrentWeaponSpread = FMath::Min(WeaponStats->MaxSpread, CurrentWeaponSpread + WeaponStats->SpreadRate);
}


//////////////////////////////////////////// Replication ///////////////////////////////////////////

void AXLRangedWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLRangedWeapon, WeaponState);
}