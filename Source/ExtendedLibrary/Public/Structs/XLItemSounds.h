#pragma once

#include "Sound/SoundCue.h"
#include "XLItemSounds.generated.h"

class USoundCue;

USTRUCT(BlueprintType)
struct FItemSounds
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* LootCue;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* EquipCue;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	USoundCue* UnequipCue;
};