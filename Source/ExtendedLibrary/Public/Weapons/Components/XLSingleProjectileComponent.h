#pragma once

#include "Weapons/Components/Interfaces/XLProjectileComponent.h"
#include "XLSingleProjectileComponent.generated.h"

class AXLProjectile;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLSingleProjectileComponent : public UXLProjectileComponent
{
	GENERATED_BODY()

public:
	UXLSingleProjectileComponent();
	void InitializeComponent() override;

public:

	UFUNCTION(Reliable, Client)
	void Fire();

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFireProjectile(FVector Origin, FVector ShootDir);

	void AppyProjectileData(AXLProjectile* Projectile);
};
