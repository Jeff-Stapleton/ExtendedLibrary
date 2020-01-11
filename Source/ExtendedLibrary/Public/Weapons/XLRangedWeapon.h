#pragma once

#include "XLWeapon.h"
#include "XLWeaponAnimationManager.h"
#include "XLWeaponSoundManager.h"
#include "XLRangedWeaponCan.h"
#include "XLRecoilData.h"

#include "XLRangedWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponAimDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadEventDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLRangedWeapon : public AXLWeapon
{
	GENERATED_BODY()

	virtual void SetOwner(AActor * NewOwner) override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FWeaponStateDelegate WeaponStateDelegate;

	UPROPERTY(BlueprintAssignable)
	FWeaponAimDelegate WeaponAimDelegate;

	UPROPERTY(BlueprintAssignable)
	FFireEventDelegate FireEventDelegate;

	UPROPERTY(BlueprintAssignable)
	FReloadEventDelegate ReloadEventDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<class UXLAimingComponent> AimingComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<class UXLProjectileComponent> ProjectileComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<class UXLReloadComponent> ReloadComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<class UXLRecoilComponent> RecoilComponentBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	TSubclassOf<class UXLFireComponent> FiringComponentBP;

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	class UXLAimingComponent* AimingComponent;

	UPROPERTY(BlueprintReadWrite, Category = Firing)
	class UXLFireComponent* FiringComponent;

	UPROPERTY(BlueprintReadWrite, Category = Ballistics)
	class UXLProjectileComponent* ProjectileComponent;

	UPROPERTY(BlueprintReadWrite, Category = Ammo)
	class UXLReloadComponent* ReloadComponent;

	UPROPERTY(BlueprintReadWrite, Category = Firing)
	class UXLRecoilComponent* RecoilComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	class UXLWeaponStats* WeaponStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class UXLWeaponSoundManager* WeaponSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UXLWeaponAnimationManager* WeaponAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	class UXLWeaponEffectManager* WeaponEffects;

	UPROPERTY(BlueprintReadWrite, Replicated)
	TEnumAsByte<EWeaponState::Type> WeaponState;;

	float CurrentWeaponSpread;

	AXLRangedWeapon();

	virtual void Destroyed() override;

	virtual void BeginPlay() override;

////////////////////////////////////////// Input handlers //////////////////////////////////////////

	UFUNCTION()
	void OnAiming();

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