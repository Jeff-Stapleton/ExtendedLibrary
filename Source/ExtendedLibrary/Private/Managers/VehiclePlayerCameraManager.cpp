// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "VehiclePlayerCameraManager.h"

AVehiclePlayerCameraManager::AVehiclePlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseClientSideCameraUpdates = false;
	bAlwaysApplyModifiers = true;
}

