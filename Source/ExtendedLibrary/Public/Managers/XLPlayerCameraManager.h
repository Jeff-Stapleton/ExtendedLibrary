// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "XLPlayerCameraManager.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	AXLPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Character")
	float NormalFOV;
	UPROPERTY(BlueprintReadWrite, Category = "XL|Character")
	float TargetFOV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Character")
	float FOVSpeed;

	virtual void UpdateCamera(float DeltaTime) override;	
};
