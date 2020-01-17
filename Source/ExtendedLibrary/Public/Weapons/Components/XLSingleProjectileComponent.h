#pragma once

#include "XLRangedWeapon.h"
#include "XLProjectile.h"
#include "XLProjectileData.h"
#include "XLProjectileComponent.h"
#include "XLSingleProjectileComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSingleProjectileComponent : public UXLProjectileComponent
{
	GENERATED_BODY()

	UXLSingleProjectileComponent();
	void InitializeComponent() override;

public:

	UFUNCTION()
	void Fire();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

	void AppyProjectileData(AXLProjectile* Projectile);
};