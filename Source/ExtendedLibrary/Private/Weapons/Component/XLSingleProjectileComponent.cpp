#include "ExtendedLibraryPCH.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/XLSingleProjectileComponent.h"

UXLSingleProjectileComponent::UXLSingleProjectileComponent()
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
}

void UXLSingleProjectileComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->FireEventDelegate.AddDynamic(this, &UXLSingleProjectileComponent::Fire);
}

void UXLSingleProjectileComponent::Fire_Implementation()
{
	const FVector Start = GetWeapon()->GetMuzzleLocation();

	//Access this Via the weapon
	const FVector End = GetWeapon()->AimingComponent->GetAdjustedAim(); // No more aiming component --  handle it in this class

	ServerFireProjectile(Start, End);
}

bool UXLSingleProjectileComponent::ServerFireProjectile_Validate(FVector Origin, FVector ShootDir)
{
	return true;
}

void UXLSingleProjectileComponent::ServerFireProjectile_Implementation(FVector Origin, FVector ShootDir)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLProjectile* Projectile = Cast<AXLProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileData.ProjectileClass, SpawnTM));
	if (Projectile)
	{
		//Projectile->Instigator = Instigator;
		Projectile->SetOwner(GetWeapon());
		AppyProjectileData(Projectile); // Thinking about making projectiles completely independent
		FVector test = (ShootDir - Origin).GetSafeNormal();
		Projectile->InitVelocity(test); 

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

void UXLSingleProjectileComponent::AppyProjectileData(AXLProjectile* Projectile)
{
	Projectile->ProjectileData = ProjectileData;
}
