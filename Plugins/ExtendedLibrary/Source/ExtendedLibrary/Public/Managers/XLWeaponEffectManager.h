#pragma once

#include "Components/ActorComponent.h"
#include "XLWeaponEffectManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponEffectManager : public UActorComponent
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	bool bLoopedMuzzleFX;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	FName MuzzleFXPoint;

	UPROPERTY(EditDefaultsOnly, Category = MuzzleFX)
	UParticleSystem* MuzzleFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	FName TrailTargetParam;

	UPROPERTY(EditDefaultsOnly, Category = TrailFX)
	UParticleSystem* TrailFX;

	UPROPERTY(EditDefaultsOnly, Category = CameraShake)
	TSubclassOf<UCameraShake> FireCameraShake;

public:
	UXLWeaponEffectManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};