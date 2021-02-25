// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "XLEffectKeyPair.generated.h"

USTRUCT(BlueprintType)
struct FEffectKeyPair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Effect")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Effect")
	FActiveGameplayEffectHandle EffectHandle;

	FEffectKeyPair();

	FEffectKeyPair(FName id, FActiveGameplayEffectHandle handle);
};
