#pragma once

#include "Components/ActorComponent.h"
#include "XLItemAnimations.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FItemAnimations
{
	GENERATED_BODY()

	/** equip animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* LootAnim;

	/** holster animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* EquipAnim;

	/** melee animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* UnequipAnim;
};