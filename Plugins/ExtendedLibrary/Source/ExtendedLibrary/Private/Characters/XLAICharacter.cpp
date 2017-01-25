// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLAICharacter.h"
#include "XLAIController.h"

AXLAICharacter::AXLAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AIControllerClass = AXLAIController::StaticClass();

	//UpdatePawnMeshes();

	bUseControllerRotationYaw = true;
}

/*bool AXLAICharacter::IsFirstPerson() const
{
	return false;
}*/

void AXLAICharacter::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}
