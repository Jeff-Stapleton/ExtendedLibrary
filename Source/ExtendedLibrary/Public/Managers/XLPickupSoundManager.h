#pragma once

#include "Components/ActorComponent.h"
#include "XLPickupSoundManager.generated.h"

class USoundCue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLPickupSoundManager : public UActorComponent
{
	GENERATED_BODY()

public:

	/** sound played when player picks it up */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	USoundCue* PickupSound;

	/** sound played on respawn */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	USoundCue* RespawnSound;

public:
	UXLPickupSoundManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};