// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerState.h"

AXLPlayerState::AXLPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	TeamNumber = 0;
}

int32 AXLPlayerState::GetTeamNum() const
{
	return TeamNumber;
}
