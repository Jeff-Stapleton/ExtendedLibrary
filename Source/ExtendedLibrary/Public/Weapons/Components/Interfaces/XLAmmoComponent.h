#pragma once

#include "Enums/XLAmmoComponentState.h"
#include "Structs/XLAmmoComponentConfig.h"
#include "XLAmmoComponent.generated.h"

class AXLRangedWeapon;
class AXLProjectile;

UCLASS()
class EXTENDEDLIBRARY_API UXLAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentClipAmmo;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|WeaponComponent")
	FAmmoComponentConfig AmmoConfig;

	UPROPERTY(BlueprintReadWrite, Category = "XL|WeaponComponent")
	TEnumAsByte<EAmmoComponentState::Type> AmmoComponentState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Weapon")
	TSubclassOf<AXLProjectile> Projectile;

	UXLAmmoComponent();
	void InitializeComponent() override;
	void BeginPlay() override;

	AXLRangedWeapon* GetWeapon();

	UFUNCTION()
	virtual void Reload();

	UFUNCTION()
	virtual void ConsumeAmmo();
};
