// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAIController.h"
#include "XLAI.h"

AXLAI::AXLAI()
{
	AIControllerClass = AXLAIController::StaticClass();

	bUseControllerRotationYaw = true;
}

void AXLAI::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}


