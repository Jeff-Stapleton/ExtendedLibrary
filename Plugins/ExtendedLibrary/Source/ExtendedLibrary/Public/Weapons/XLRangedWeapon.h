#pragma once

#include "GameFramework/Actor.h"
#include "XLRangedWeapon.generated.h"

UCLASS()
class AXLRangedWeapon : public AXLWeapon
{
	GENERATED_BODY()
	
public:
	AXLRangedWeapon();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

	////////////////////////////////////////// Input handlers //////////////////////////////////////////

	virtual bool StartAttack();
	virtual void StopAttack();

	virtual void StartReload();
	virtual void StopReload();

	void ProcessInstantHit(const FHitResult & Impact, const FVector & Origin, const FVector & ShootDir, int32 RandomSeed, float ReticleSpread);

	///////////////////////////////////////// Aiming Helpers /////////////////////////////////////////

	void SpawnTrailEffect(const FVector& EndPoint);
	void SpawnImpactEffects(const FHitResult & Impact);
	FHitResult GetAdjustedAim();
	FVector GetCameraAim();
	FVector GetCameraDamageStartLocation(const FVector& AimDir);
	FVector GetMuzzleLocation();
	FVector GetMuzzleDirection();
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo);
	float GetCurrentSpread() const;

	virtual void PlayAttackFX();
	virtual void StopAttackFX();

};