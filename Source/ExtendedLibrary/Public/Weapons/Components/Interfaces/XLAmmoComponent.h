#pragma once

#include "XLAmmoComponent.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API UXLAmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** The amount of ammo in each clip */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxClipAmmo = 25.0f;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Resources)
	float CurrentClipAmmo;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Resources)
	float CurrentAmmo;

	UXLAmmoComponent();
	void InitializeComponent() override;

	class AXLRangedWeapon* GetWeapon();
};
