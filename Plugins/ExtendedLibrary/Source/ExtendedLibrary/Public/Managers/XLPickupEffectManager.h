#pragma once

#include "Components/ActorComponent.h"
#include "XLPickupEffectManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLPickupEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:

	/** FX of active pickup */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* ActiveFX;

	/** FX of pickup on respawn timer */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* RespawningFX;

public:

	UXLPickupEffectManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};