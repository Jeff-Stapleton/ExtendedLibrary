#pragma once

#include "XLFireComponent.generated.h"

class UXLAmmoComponent;
class UXLAimingComponent;
class USoundCue;
class AXLRangedWeapon;
class AXLProjectile;
class AXLItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFiringEventDelegate);

UCLASS()
class EXTENDEDLIBRARY_API UXLFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Weapon")
	TSubclassOf<UXLAimingComponent> AimingComponentBP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Weapon")
	TSubclassOf<UXLAmmoComponent> AmmoComponentBP;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Weapon")
	//TSubclassOf<AXLRecoilComponent> RecoilComponent;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL | Weapon")
	//TSubclassOf<AXLMuzzleComponent> MuzzleComponent;
	UPROPERTY(EditDefaultsOnly, Category = "XL | Weapon")
	FName SpawnPoint = "Muzzle";

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	UXLAimingComponent* AimingComponent;

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	UXLAmmoComponent* AmmoComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL | Weapon")
	float TimeBetweenAttacks = 0.15f;

	FFiringEventDelegate FireEventDelegate;

protected:

	float LastAttackTime = 0.0f;
	FTimerHandle FiringTimer;

public:

	UXLFireComponent();

	void InitializeComponent() override;

	AXLItem* GetWeapon();

	UFUNCTION()
	virtual void DetermineAction();
};

//class IXLFireComponent
//{
//	GENERATED_BODY()
//
//
//	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Firing")
//	//void StartAttack();
//
//	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Firing")
//	//void StopAttack();
//};