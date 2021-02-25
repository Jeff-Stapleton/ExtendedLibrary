// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XLProgressWheel.generated.h"

class UUserWidget;

UCLASS()
class EXTENDEDLIBRARY_API UXLProgressWheel : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "IO|UI")
	float Target;

	UPROPERTY(BlueprintReadWrite, Category = "IO|UI")
	float Progress;
};
