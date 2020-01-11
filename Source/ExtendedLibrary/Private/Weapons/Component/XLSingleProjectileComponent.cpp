#include "ExtendedLibraryPCH.h"
#include "Kismet/KismetSystemLibrary.h"
#include "XLSingleProjectileComponent.h"

UXLSingleProjectileComponent::UXLSingleProjectileComponent()
{
	bWantsInitializeComponent = true;
}

void UXLSingleProjectileComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetWeapon()->FireEventDelegate.AddDynamic(this, &UXLSingleProjectileComponent::Fire);
}

void UXLSingleProjectileComponent::Fire()
{
	const FVector Start = GetWeapon()->GetMuzzleLocation();

	//Access this Via the weapon
	const FVector End = GetWeapon()->AimingComponent->GetAdjustedAim();

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
		AppyProjectileData(Projectile);
		FVector test = (ShootDir - Origin).GetSafeNormal();
		Projectile->InitVelocity(test);

		UGameplayStatics::FinishSpawningActor(Projectile, SpawnTM);
	}
}

void UXLSingleProjectileComponent::AppyProjectileData(AXLProjectile* Projectile)
{
	Projectile->ProjectileData = ProjectileData;
}