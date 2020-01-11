// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLProjectile.h"

AXLProjectile::AXLProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->AlwaysLoadOnClient = true;
	CollisionComp->AlwaysLoadOnServer = true;
	CollisionComp->bTraceComplexOnMove = true;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	RootComponent = CollisionComp;

	ParticleComp = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleComp"));
	ParticleComp->bAutoActivate = false;
	ParticleComp->bAutoDestroy = false;
	ParticleComp->SetupAttachment(RootComponent);

	MovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->InitialSpeed = 2000.0f;
	MovementComp->MaxSpeed = 200000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bReplicateMovement = true;
}

void AXLProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MovementComp->OnProjectileStop.AddDynamic(this, &AXLProjectile::OnImpact);
	CollisionComp->MoveIgnoreActors.Add(Instigator);

	//AShooterWeapon_Projectile* OwnerWeapon = Cast<AShooterWeapon_Projectile>(GetOwner());
	//if (OwnerWeapon)
	//{
	//	OwnerWeapon->ApplyWeaponConfig(WeaponConfig);
	//}

	SetLifeSpan(1.0f/*WeaponConfig.ProjectileLife*/);
	//MyController = GetInstigatorController();
}

void AXLProjectile::InitVelocity(FVector& ShootDirection)
{
	if (MovementComp)
	{
		MovementComp->Velocity = ShootDirection * MovementComp->InitialSpeed;
	}
}

void AXLProjectile::OnImpact(const FHitResult& HitResult)
{
	if (Role == ROLE_Authority)
	{
		if (ProjectileData.ExplosionRadius > 0)
		{
			Explode(HitResult);
		}
		else
		{
			Hit(HitResult);
		}
		DisableAndDestroy();
	}
}

void AXLProjectile::Explode(const FHitResult& HitResult)
{
	//if (ParticleComp)
	//{
	//	ParticleComp->Deactivate();
	//}

	// effects and damage origin shouldn't be placed inside mesh at impact point
	const FVector NudgedImpactLocation = HitResult.ImpactPoint + HitResult.ImpactNormal * 10.0f;

	if (ProjectileData.ExplosionDamage > 0 && ProjectileData.DamageType)
	{
		UGameplayStatics::ApplyRadialDamage(this, ProjectileData.ExplosionDamage, NudgedImpactLocation, ProjectileData.ExplosionRadius, ProjectileData.DamageType, TArray<AActor*>(), this, GetInstigatorController());
	}

	//if (ExplosionTemplate)
	//{
	//	FTransform const SpawnTransform(Impact.ImpactNormal.Rotation(), NudgedImpactLocation);
	//	AShooterExplosionEffect* const EffectActor = GetWorld()->SpawnActorDeferred<AShooterExplosionEffect>(ExplosionTemplate, SpawnTransform);
	//	if (EffectActor)
	//	{
	//		EffectActor->SurfaceHit = Impact;
	//		UGameplayStatics::FinishSpawningActor(EffectActor, SpawnTransform);
	//	}
	//}

	//bExploded = true;
}

void AXLProjectile::Hit(const FHitResult& HitResult)
{
	FPointDamageEvent PointDmg;
	PointDmg.DamageTypeClass = ProjectileData.DamageType;
	PointDmg.HitInfo = HitResult;
	PointDmg.ShotDirection = HitResult.ImpactPoint;
	PointDmg.Damage = ProjectileData.ExplosionDamage;

	HitResult.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, GetInstigatorController(), this);
}

void AXLProjectile::DisableAndDestroy()
{
	//UAudioComponent* ProjAudioComp = FindComponentByClass<UAudioComponent>();
	//if (ProjAudioComp && ProjAudioComp->IsPlaying())
	//{
	//	ProjAudioComp->FadeOut(0.1f, 0.f);
	//}

	MovementComp->StopMovementImmediately();

	// give clients some time to show explosion
	SetLifeSpan(2.0f);
}