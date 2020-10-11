#pragma once

#include "XLFireComponentConfig.generated.h"

USTRUCT(BlueprintType)
struct FFireComponentConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL | Weapon")
	float TimeBetweenAttacks = 0.15f;
};