// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPlayerCameraManager.h"

AXLPlayerCameraManager::AXLPlayerCameraManager(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	TargetFOV = 90.0f;
	FOVSpeed = 20.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	ViewTargetOffset = FVector(200.0f, 200.0f, 200.0f);

	bAlwaysApplyModifiers = true;
	DefaultFOV = NormalFOV;
}

void AXLPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);
	
	if (TargetFOV != DefaultFOV)
	{
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, FOVSpeed);
		SetFOV(DefaultFOV);
	}
}



