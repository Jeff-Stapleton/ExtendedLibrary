// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "XLGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDLIBRARY_API UXLGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
public: 	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "XL|Effect")
	FName EffectId;
};
