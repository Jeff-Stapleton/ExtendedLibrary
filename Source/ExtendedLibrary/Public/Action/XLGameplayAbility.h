// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Enums/XLAbilityType.h"
#include "XLGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDLIBRARY_API UXLGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XL|Ability")
	FName AbilityId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XL|Ability")
	EAbilityType AbilityType = EAbilityType::None;

	UXLGameplayAbility();
};
