// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XLAbilityKeyPair.generated.h"

USTRUCT(BlueprintType)
struct FAbilityKeyPair
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Ability")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Ability")
	FGameplayAbilitySpecHandle AbilityHandle;

	FAbilityKeyPair();

	FAbilityKeyPair(FName id, FGameplayAbilitySpecHandle handle);
};
