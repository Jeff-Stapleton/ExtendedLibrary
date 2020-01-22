// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerCameraManager.h"

AXLPlayerCameraManager::AXLPlayerCameraManager(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	NormalFOV = 90.0f;
	ViewPitchMin = -87.0f;
	ViewPitchMax = 87.0f;
	ViewTargetOffset = FVector(200.0f, 200.0f, 200.0f);

	bAlwaysApplyModifiers = true;
}

void AXLPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	AXLCharacter* Character = PCOwner ? Cast<AXLCharacter>(PCOwner->GetPawn()) : NULL;
	if (Character)
	{
		float TargetFOV = NormalFOV;
		if (Character->TargetingState == ETargetingState::ADS && Character->CurrentItem != MAX_int32)
		{
			AXLItem* Weapon = Cast<AXLItem>(Character->CharacterInventory->GetItem(Character->CurrentItem));
			TargetFOV = 45.0f;//Weapon->WeaponStats->TargetingFOV;
		}
		
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 20.0f);
	}

	Super::UpdateCamera(DeltaTime);

	if (Character)
	{
		Character->OnCameraUpdate(GetCameraLocation(), GetCameraRotation());
	}
}



