#pragma once

#include "XLProjectileData.generated.h"

class AXLProjectile;

USTRUCT(BlueprintType)
struct FXLProjectileData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AXLProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float ProjectileLife;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	int32 ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float Force;

	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	TSubclassOf<UDamageType> DamageType;

	FXLProjectileData()
	{
		ProjectileClass = NULL;
		ProjectileLife = 10.0f;
		ExplosionDamage = 100;
		ExplosionRadius = 0.0f;
		Force = 10000.0f;
		DamageType = UDamageType::StaticClass();
	}
};