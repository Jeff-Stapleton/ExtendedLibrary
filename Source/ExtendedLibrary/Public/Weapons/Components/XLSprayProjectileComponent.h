#pragma once

#include "XLRangedWeapon.h"
#include "XLProjectile.h"
#include "XLProjectileData.h"
#include "XLProjectileComponent.h"
#include "XLRangedWeapon.h"
#include "XLSprayProjectileComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSprayProjectileComponent : public UXLProjectileComponent
{
	GENERATED_BODY()

	UXLSprayProjectileComponent();
	void InitializeComponent() override;

public:

	/** This is the number of projectiles in the spray of each firing event */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float NumberOfProjectiles = 10.0f;

	UFUNCTION()
	void Fire();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

	void AppyProjectileData(AXLProjectile* Projectile);
};