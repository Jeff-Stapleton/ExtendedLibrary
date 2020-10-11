#pragma once

#include "XLAmmoComponentConfig.generated.h"

USTRUCT(BlueprintType)
struct FAmmoComponentConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxClipAmmo = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxAmmo = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float ReloadDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteClip = false;
};