#pragma once

#include "Components/ActorComponent.h"
#include "Enums/XLWeaponState.h"
#include "XLWeaponEffectManager.generated.h"

class AXLImpactEffect;
class AXLRangedWeapon;
class UMatineeCameraShake;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponEffectManager : public UActorComponent
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	FName MuzzleFXPoint;
	
	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	FName TrailTargetParam;

	UPROPERTY(EditDefaultsOnly, Category = ImpactFX)
	TSubclassOf<AXLImpactEffect> ImpactTemplate;

	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UMatineeCameraShake> FireCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	UParticleSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	UParticleSystem* TrailFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	AXLRangedWeapon* Owner;

public:
	UXLWeaponEffectManager();

	void InitializeComponent() override;

	UFUNCTION()
	void DetermineAction();

protected:
	UFUNCTION(Reliable, NetMulticast)
	void ActivateMuzzlePSC();

	UFUNCTION(Reliable, NetMulticast)
	void DeactivateMuzzlePSC();

};