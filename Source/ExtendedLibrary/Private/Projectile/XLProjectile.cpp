// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Projectiles/XLImpactFX.h"
#include "Projectiles/XLProjectile.h"

AXLProjectile::AXLProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->AlwaysLoadOnClient = true;
	CollisionComp->AlwaysLoadOnServer = true;
	CollisionComp->bTraceComplexOnMove = true;
	CollisionComp->bReturnMaterialOnMove = true;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	RootComponent = CollisionComp;

	MovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->InitialSpeed = 18750.0f;
	MovementComp->MaxSpeed = 200000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 1.0f;

	AudioComp = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);

	TrailFX = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("TrailFX"));
	TrailFX->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	SetReplicatingMovement(true);
}

void AXLProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsTactical)
	{
		GetWorldTimerManager().SetTimer(DetonationTimer, this, &AXLProjectile::Explode, DetonationTime, false);
	}
	else
	{
		MovementComp->OnProjectileStop.AddDynamic(this, &AXLProjectile::OnImpact);
	}

	CollisionComp->MoveIgnoreActors.Add(GetInstigator());
	SetLifeSpan(ProjectileData.ProjectileLife);
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
	if (GetLocalRole() == ROLE_Authority)
	{
		if (ProjectileData.ExplosionRadius > 0)
		{
			Explode();
		}
		else
		{
			Hit(HitResult);
		}
	}
}

void AXLProjectile::Explode()
{
	const FVector NudgedImpactLocation = GetActorLocation() + GetActorRotation().Vector() * 10.0f;

	if (ProjectileData.ExplosionDamage > 0 && ProjectileData.DamageType)
	{
		UGameplayStatics::ApplyRadialDamage(this, ProjectileData.ExplosionDamage, NudgedImpactLocation, ProjectileData.ExplosionRadius, ProjectileData.DamageType, TArray<AActor*>(), this, GetInstigatorController());
	}
	Explosion();
	bImpact = true;
}

void AXLProjectile::Hit(const FHitResult& HitResult)
{
	FPointDamageEvent PointDmg;
	PointDmg.DamageTypeClass = ProjectileData.DamageType;
	PointDmg.HitInfo = HitResult;
	PointDmg.ShotDirection = HitResult.ImpactPoint;

	if (HitResult.BoneName == "head")
	{
		PointDmg.Damage = ProjectileData.ExplosionDamage * 2;
	}
	else
	{
		PointDmg.Damage = ProjectileData.ExplosionDamage;
	}
	if (HitResult.GetActor())
	{
		HitResult.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, GetInstigatorController(), this);
	}

	Impact(HitResult);
	bImpact = true;
	DisableAndDestroy();
}

void AXLProjectile::Impact(const FHitResult& HitResult)
{
	if (ImpactFX && HitResult.bBlockingHit)
	{
		FHitResult UseImpact = HitResult;

		FRotator MyRotator = FRotationMatrix::MakeFromZ(HitResult.ImpactNormal).Rotator();
		FTransform const SpawnTransform(MyRotator, HitResult.ImpactPoint);
		AXLImpactFX* const FXActor = GetWorld()->SpawnActorDeferred<AXLImpactFX>(ImpactFX, SpawnTransform);
		if (FXActor)
		{
			FXActor->SurfaceHit = UseImpact;
			UGameplayStatics::FinishSpawningActor(FXActor, SpawnTransform);
		}

	}
}

void AXLProjectile::Explosion()
{
	if (ImpactFX)
	{
		FTransform const SpawnTransform(GetActorRotation(), GetActorLocation());
		AXLImpactFX* const FXActor = GetWorld()->SpawnActorDeferred<AXLImpactFX>(ImpactFX, SpawnTransform);
		if (FXActor)
		{
			UGameplayStatics::FinishSpawningActor(FXActor, SpawnTransform);
		}
	}
	DisableAndDestroy();
}

void AXLProjectile::OnRep_Impact()
{
	FVector ProjDirection = GetActorForwardVector();

	const FVector StartTrace = GetActorLocation() - ProjDirection * 200;
	const FVector EndTrace = GetActorLocation() + ProjDirection * 150;

	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, this);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, COLLISION_PROJECTILE, TraceParams);

	Impact(Hit);
}

void AXLProjectile::DisableAndDestroy()
{
	if (TrailFX)
	{
		TrailFX->Deactivate();
	}
	//UAudioComponent* ProjAudioComp = FindComponentByClass<UAudioComponent>();
	//if (ProjAudioComp && ProjAudioComp->IsPlaying())
	//{
	//	ProjAudioComp->FadeOut(0.1f, 0.f);
	//}

	MovementComp->StopMovementImmediately();

	// give clients some time to show explosion
	SetLifeSpan(0.1);
}

void AXLProjectile::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLProjectile, bImpact);
}
