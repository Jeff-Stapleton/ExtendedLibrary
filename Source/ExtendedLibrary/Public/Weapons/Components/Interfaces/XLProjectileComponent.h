#pragma once

#include "Projectiles/XLProjectile.h"
#include "Structs/XLProjectileData.h"
#include "XLProjectileComponent.generated.h"

class AXLRangedWeapon;

UCLASS()
class EXTENDEDLIBRARY_API UXLProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UXLProjectileComponent();
	void InitializeComponent() override;

	AXLRangedWeapon* GetWeapon();

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FXLProjectileData ProjectileData;
};
