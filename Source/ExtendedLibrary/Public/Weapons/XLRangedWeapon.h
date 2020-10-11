#pragma once

#include "Items/XLItem.h"
#include "Cans/XLRangedWeaponCan.h"
#include "Enums/XLTargetingState.h"
#include "Enums/XLWeaponState.h"
#include "XLRangedWeapon.generated.h"

class UXLAimingComponent;
class UXLProjectileComponent;
class UXLAmmoComponent;
class UXLRecoilComponent;
class UXLFireComponent;
class UXLTargetingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponAimDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadEventDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLRangedWeapon : public AXLItem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FWeaponStateDelegate WeaponStateDelegate;

	UPROPERTY(BlueprintAssignable)
	FWeaponAimDelegate WeaponAimDelegate;

	UPROPERTY(BlueprintAssignable)
	FWeaponAimDelegate TargetingStateDelegate;

	UPROPERTY(BlueprintAssignable)
	FFireEventDelegate FireEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FReloadEventDelegate ReloadEventDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLAimingComponent> AimingComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLProjectileComponent> ProjectileComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLAmmoComponent> ReloadComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLRecoilComponent> RecoilComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLFireComponent> FiringComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<UXLTargetingComponent> TargetingComponentBP;

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	UXLAimingComponent* AimingComponent;

	UPROPERTY(BlueprintReadWrite, Category = Firing)
	UXLFireComponent* FiringComponent;

	UPROPERTY(BlueprintReadWrite, Category = Ballistics)
	UXLProjectileComponent* ProjectileComponent;

	UPROPERTY(BlueprintReadWrite, Category = Ammo)
	UXLAmmoComponent* ReloadComponent;

	UPROPERTY(BlueprintReadWrite, Category = Firing)
	UXLRecoilComponent* RecoilComponent;

	UPROPERTY(BlueprintReadWrite, Category = Targeting)
	UXLTargetingComponent* TargetingComponent;

	UPROPERTY(BlueprintReadWrite, Replicated)
	TEnumAsByte<EWeaponState::Type> WeaponState;

	UPROPERTY(BlueprintReadWrite, Replicated)
	TEnumAsByte<ETargetingState::Type> TargetingState;

	float CurrentWeaponSpread;

	AXLRangedWeapon();

	virtual void Destroyed() override;

	virtual void BeginPlay() override;

	virtual void SetOwner(AActor * NewOwner) override;

////////////////////////////////////////// Input handlers //////////////////////////////////////////

	UFUNCTION()
	void OnAiming();

	void StartAiming();
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerStartAiming();

	void StopAiming();
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerStopAiming();

	virtual void StartAttack();
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerStartAttack();

	virtual void StopAttack();
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerStopAttack();

	virtual void Reload();
	UFUNCTION(Reliable, Server, WithValidation)
	virtual void ServerReload();

	void ApplyAttackForce(const FHitResult& Impact);

	FVector GetMuzzleLocation();

	float GetCurrentSpread() const;
	void SetCurrentSpread();

};
