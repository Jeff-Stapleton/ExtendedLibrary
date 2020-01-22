#pragma once

#include "XLRangedWeapon.h"
#include "XLProjectile.h"
#include "XLProjectileData.h"
#include "XLProjectileComponent.h"
#include "XLRangedWeapon.h"
#include "XLSingleProjectileComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSingleProjectileComponent : public UXLProjectileComponent
{
	GENERATED_BODY()

public:
	UXLSingleProjectileComponent();
	void InitializeComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxDamage = 19.0f;

	/** The minimum amount of damage dealt possible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MinDamage = 19.0f;

	/** type of damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TSubclassOf<UDamageType> DamageType;

	/** The amount of force the attack applies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Force = 10000.0f;

	/** Weapon ranges */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxRange = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	UParticleSystem* TrailFX;

public:

	UFUNCTION()
	void Fire();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

	void AppyProjectileData(AXLProjectile* Projectile);
};