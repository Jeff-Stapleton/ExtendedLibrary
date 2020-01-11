#include "XLRecoilData.generated.h"

#pragma once

USTRUCT(BlueprintType)
struct FRecoilData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	float VerticalRecoil = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float HorizontalRecoil = 0.0f;

	FORCEINLINE bool IsZero()
	{
		return VerticalRecoil == 0.0f && HorizontalRecoil == 0.0f;
	}

	FORCEINLINE void Reset()
	{
		VerticalRecoil = 0.0f;
		HorizontalRecoil = 0.0f;
	}

	FORCEINLINE bool operator==(const FRecoilData &A) const
	{
		return FMath::Abs(VerticalRecoil - A.VerticalRecoil) < 0.1 && FMath::Abs(HorizontalRecoil - A.HorizontalRecoil) < 0.1;
	}

	FORCEINLINE bool operator!=(const FRecoilData &A) const
	{
		return !operator==(A);
	}
};