#include "XLHitScanInfo.generated.h"

#pragma once

USTRUCT()
struct FHitScanInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector End;

	UPROPERTY()
	FHitResult Impact;
};