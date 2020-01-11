#pragma once

#include "Components/ActorComponent.h"
#include "XLImpactEffect.h"
#include "XLWeaponEffectManager.generated.h"

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
	TSubclassOf<UCameraShake> FireCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	UParticleSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	UParticleSystem* TrailFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	class AXLRangedWeapon* Owner;

public:
	UXLWeaponEffectManager();

	void InitializeComponent() override;

	UFUNCTION()
	void DetermineAction();

protected:
	void ActivateMuzzlePSC();
	void DeactivateMuzzlePSC();

};