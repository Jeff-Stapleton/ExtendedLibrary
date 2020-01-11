#pragma once

#include "GameFramework/Actor.h"
#include "XLProjectileData.h"
#include "XLProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract, Blueprintable)
class AXLProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

public:

	FXLProjectileData ProjectileData;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UParticleSystemComponent* ParticleComp;

public:

	void InitVelocity(FVector& ShootDirection);

	UFUNCTION()
	void OnImpact(const FHitResult& HitResult);

private:

	void Explode(const FHitResult& HitResult);

	void Hit(const FHitResult& HitResult);

	void DisableAndDestroy();
};