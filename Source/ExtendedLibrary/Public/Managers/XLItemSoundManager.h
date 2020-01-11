#pragma once

#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "XLItemSoundManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLItemSoundManager : public UActorComponent
{
	GENERATED_BODY()

public:

	/** equip sound */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* LootCue;

	/** holster sound */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* EquipCue;

	/** melee sound */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* UnequipCue;

public:
	UXLItemSoundManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};