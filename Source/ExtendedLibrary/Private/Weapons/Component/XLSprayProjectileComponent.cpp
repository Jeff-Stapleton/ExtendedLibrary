#include "ExtendedLibraryPCH.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/XLSprayProjectileComponent.h"

UXLSprayProjectileComponent::UXLSprayProjectileComponent()
{
	bWantsInitializeComponent = true;
}

void UXLSprayProjectileComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->FireEventDelegate.AddDynamic(this, &UXLSprayProjectileComponent::Fire);
}

void UXLSprayProjectileComponent::Fire()
{
	for (int i = 0; i < NumberOfProjectiles; i++)
	{
		const FVector Start = GetWeapon()->GetMuzzleLocation();
		const FVector End = GetWeapon()->AimingComponent->GetAdjustedAim();

		ServerFireProjectile(Start, End);
	}
}

bool UXLSprayProjectileComponent::ServerFireProjectile_Validate(FVector Origin, FVector ShootDir)
{
	return true;
}

void UXLSprayProjectileComponent::ServerFireProjectile_Implementation(FVector Origin, FVector ShootDir)
{
	FTransform SpawnTM(FVector::ZeroVector.Rotation(), Origin);
	AXLProjectile* Projectile = Cast<AXLProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileData.ProjectileClass, SpawnTM));
	if (Projectile)
	{
		//Projectile->Instigator = Instigator;
		Projectile->SetOwner(GetWeapon());
		AppyProjectileData(Projectile);
		FVector test = (ShootDir - Origin).GetSafeNormal();
		Projectile->InitVelocity(test);

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

void UXLSprayProjectileComponent::AppyProjectileData(AXLProjectile* Projectile)
{
	Projectile->ProjectileData = ProjectileData;
}
