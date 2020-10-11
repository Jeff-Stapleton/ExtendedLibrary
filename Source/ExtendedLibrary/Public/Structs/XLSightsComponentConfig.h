#pragma once

#include "XLSightsComponentConfig.generated.h"

USTRUCT(BlueprintType)
struct FSightsComponentConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float DefaultFOV = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float FOV = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float Speed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float BlindDuration = 0.1;
};