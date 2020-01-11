#pragma once

#include "XLProjectile.h"
#include "XLProjectileData.h"
#include "XLProjectileComponent.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API UXLProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UXLProjectileComponent();
	void InitializeComponent() override;

	class AXLRangedWeapon* GetWeapon();

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FXLProjectileData ProjectileData;
};